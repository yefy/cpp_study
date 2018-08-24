#include "skp_protobuf_test.h"
#include "gtest/gtest.h"
#include "src/skp_common.h"
#include "src/skp_log.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#include <iostream>
#include <fstream>
#include "caffe.pb.h"
#include "google/protobuf/text_format.h"

using namespace std;
using namespace caffe;

SKP_TEST(protobuf, protobuf_test1)
{
    Person person;

    person.set_name("flamingo");
    person.set_age(18);
    person.set_email("majianfei1023@gmail.com");
    person.mutable_phone()->set_number("135525");
    person.PrintDebugString();

    printf("******************************* \n");

    std::string output1;
    person.SerializeToString(&output1);
    printf("output1 = %s \n", output1.c_str());

    printf("******************************* \n");


    std::string output2;
    google::protobuf::TextFormat::PrintToString(person, &output2);
    printf("output2 = %s \n", output2.c_str());

    printf("******************************* \n");

    Person person2;
    google::protobuf::TextFormat::ParseFromString(output2, &person2);
    person2.PrintDebugString();

    printf("******************************* \n");
    const google::protobuf::Descriptor* pNodeDescriptor   = person2.GetDescriptor();
    ASSERT_TRUE(pNodeDescriptor != NULL);
    printf("pNodeDescriptor = %s \n", pNodeDescriptor->DebugString().c_str());

    const google::protobuf::FieldDescriptor* pAttrField   = pNodeDescriptor->FindFieldByName("name");
    ASSERT_TRUE(pAttrField != NULL);

    std::string output3;
    google::protobuf::TextFormat::PrintFieldValueToString(person2, pAttrField, 1, &output3);
    printf("output3 = %s \n", output3.c_str());

//    const string input = "flamingo_flamingo";
//    google::protobuf::TextFormat::ParseFieldValueFromString(input, pAttrField, &person2);
//    google::protobuf::TextFormat::

//    output3 = "";
//    google::protobuf::TextFormat::PrintFieldValueToString(person2, pAttrField, 1, &output3);
//    printf("output3 = %s \n", output3.c_str());


    printf("******************************* \n");
    //std::string type_name = Person::descriptor()->full_name();
    std::string type_name = "caffe.Person";
    printf("type_name = %s \n", type_name.c_str());

    const google::protobuf::Descriptor* descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
    //assert(descriptor == Person::descriptor());
    cout << "FindMessageTypeByName() = " << descriptor << endl;
    cout << "T::descriptor()         = " << Person::descriptor() << endl;
    cout << endl;

    const google::protobuf::Message* prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
    //assert(prototype == &Person::default_instance());
    cout << "GetPrototype()        = " << prototype << endl;
    cout << "T::default_instance() = " << &Person::default_instance() << endl;
    cout << endl;

    printf("******************************* \n");

    //Person* new_obj = dynamic_cast<Person *>(prototype->New());
    google::protobuf::Message* new_obj = prototype->New();
    assert(new_obj != NULL);
    assert(new_obj != prototype);
    //assert(typeid(*new_obj) == typeid(Person::default_instance()));
    //cout << "prototype->New() = " << new_obj << endl;
    //cout << endl;
    //delete new_obj;


    google::protobuf::TextFormat::ParseFromString(output2, new_obj);
    new_obj->PrintDebugString();


//    const google::protobuf::FieldDescriptor field;
//    int index = 0;
//    std::string output3;
//    google::protobuf::TextFormat::PrintFieldValueToString(person, &field, index, &output3);
//    printf("output3 = %s \n", output3.c_str());
}



//! 利用类型名字构造对象.
/*!
 * @Param type_name 类型名字，比如 "Test.TestMessage".
 * @Return 对象指针，new 出来的，使用者负责释放.
 */
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include "test.pb.h" // 这是protoc给你生成的文件

SKP_TEST(protobuf, protobuf_test2)
{
    // 先获得类型的Descriptor .
    auto descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName("T.Test");
    ASSERT_TRUE(nullptr != descriptor);

    // 利用Descriptor拿到类型注册的instance. 这个是不可修改的.
    auto prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
    ASSERT_TRUE(nullptr != prototype);

    // 构造一个可用的消息.
    auto message = prototype->New();
    // 只有当我们预先编译了test消息并且正确链接才能这么干.
    auto test = dynamic_cast<T::Test*>(message);
    // 直接调用message的具体接口
    // 其实这些接口是语法糖接口.所以并没有对应的反射机制来对应调用.
    // 反射机制实现了的Set/Get XXX系列接口，是属于Reflection的接口，接收Message作为参数.
    test->set_id(1);
    std::cout<<test->Utf8DebugString()<<std::endl;
    delete message ;
}


#include <iostream>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/dynamic_message.h>
SKP_TEST(protobuf, protobuf_test3)
{
    const std::string path = "../../../cpp_study/trunk/project_cpp/src/protobuf/";
    std::string fullPath = path + "test.proto";

    ASSERT_TRUE(access(fullPath.c_str(), 0) == 0);

    // 准备配置好文件系统
    google::protobuf::compiler::DiskSourceTree sourceTree;
    // 将当前路径映射为项目根目录 ， project_root 仅仅是个名字，你可以你想要的合法名字.
    sourceTree.MapPath("project_root","./");
    // 配置动态编译器.
    google::protobuf::compiler::Importer importer(&sourceTree, NULL);
    // 动态编译proto源文件
    //const google::protobuf::FileDescriptor *tFileDescriptor =importer.Import(fullPath.c_str());
    const google::protobuf::FileDescriptor *tFileDescriptor = importer.Import("project_root/test.proto");
    tFileDescriptor->DebugString();
    ASSERT_TRUE(nullptr != tFileDescriptor);
    // 现在可以从编译器中提取类型的描述信息.
    auto descriptor1 = importer.pool()->FindMessageTypeByName("T.Test");
    ASSERT_TRUE(nullptr != descriptor1);
    // 创建一个动态的消息工厂.
    google::protobuf::DynamicMessageFactory factory;
    // 从消息工厂中创建出一个类型原型.
    auto proto1 = factory.GetPrototype(descriptor1);
    // 构造一个可用的消息.
    auto message1= proto1->New();
    // 下面是通过反射接口给字段赋值.
    auto reflection1 = message1->GetReflection();
    auto filed1 = descriptor1->FindFieldByName("id");
    reflection1->SetInt32(message1,filed1,1);
    // 打印看看
    std::cout << message1->DebugString();
    // 删除消息.
    delete message1 ;
}


SKP_TEST(protobuf, protobuf_test4)
{
    // 拿到一个对象，不在乎怎么拿到，可以是通过反射拿到。
    // 这里简单直接的创建一个.
    T::Test p_test ;
    // 拿到对象的描述包.
    auto descriptor = p_test.GetDescriptor() ;
    // 拿到对象的反射配置.
    auto reflecter = p_test.GetReflection() ;
    // 拿到属性的描述包.
    auto field = descriptor->FindFieldByName("id");
    // 设置属性的值.
    reflecter->SetInt32(&p_test , field , 5 ) ;
    // 获取属性的值.
    std::cout<<reflecter->GetInt32(p_test , field)<< std::endl ;
}
