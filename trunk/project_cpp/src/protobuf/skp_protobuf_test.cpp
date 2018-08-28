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
using namespace google::protobuf;

SKP_TEST_ONECE(protobuf, protobuf_test1)
{
    AddressBook book;

    Person *people1 = book.add_people();
    people1->set_name("aaa");
    people1->set_age(18);
    people1->set_email("qq.com");

    Person::PhoneNumber *phone1 = people1->add_phone();
    phone1->set_number("111");
    phone1->set_type(::caffe::Person_PhoneType_MOBILE);

    Person::PhoneNumber *phone2 = people1->add_phone();
    phone2->set_number("222");
    phone2->set_type(::caffe::Person_PhoneType_HOME);

    Person::PhoneNumber *phone3 = people1->add_phone();
    phone3->set_number("333");
    phone3->set_type(::caffe::Person_PhoneType_WORK);

    people1->add_string_arg5(std::string("string_arg5"));
    people1->add_string_arg5(std::string("string_arg5"));

    people1->add_int32_arg6(6);
    people1->add_int32_arg6(6);

    people1->set_uint32_arg7(7);
    people1->set_int64_arg8(8);
    people1->set_uint64_arg9(9);
    people1->set_double_arg10(10.1);
    people1->set_float_arg11(11.11);
    people1->set_bool_arg12(false);


    Person *people2 = book.add_people();
    people2->set_name("bbb");
    people2->set_age(18);
    people2->set_email("sina.com");

    Person::PhoneNumber *phone11 = people2->add_phone();
    phone11->set_number("a111");
    phone11->set_type(::caffe::Person_PhoneType_MOBILE);

    Person::PhoneNumber *phone22 = people2->add_phone();
    phone22->set_number("b222");
    phone22->set_type(::caffe::Person_PhoneType_HOME);

    Person::PhoneNumber *phone33 = people2->add_phone();
    phone33->set_number("c333");
    phone33->set_type(::caffe::Person_PhoneType_WORK);

    people2->add_string_arg5(std::string("add_string_arg5"));
    people2->add_string_arg5(std::string("add_string_arg5"));

    people2->add_int32_arg6(66);
    people2->add_int32_arg6(66);

    people2->set_uint32_arg7(77);
    people2->set_int64_arg8(88);
    people2->set_uint64_arg9(99);
    people2->set_double_arg10(100.2);
    people2->set_float_arg11(110.22);
    people2->set_bool_arg12(true);

    printf("**************PrintDebugString***************** \n");
    book.PrintDebugString();


    std::string output1;
    book.SerializeToString(&output1);
    printf("************SerializeToString******************* \n");
    printf("%s \n", output1.c_str());

    std::string output2;
    google::protobuf::TextFormat::PrintToString(book, &output2);
    printf("*************PrintToString****************** \n");
    printf("%s \n", output2.c_str());
    log_print("%s \n", output2.c_str());

    AddressBook book2;
    google::protobuf::TextFormat::ParseFromString(output2, &book2);
    printf("*************ParseFromString****************** \n");
    book2.PrintDebugString();

  /*
    printf("******************************* \n");
    const google::protobuf::Descriptor* pNodeDescriptor   = book2.GetDescriptor();
    ASSERT_TRUE(pNodeDescriptor != NULL);
    printf("pNodeDescriptor = %s \n", pNodeDescriptor->DebugString().c_str());

    const google::protobuf::FieldDescriptor* pAttrField   = pNodeDescriptor->FindFieldByName("people");
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
*/
}


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>

#define SPACE_NUMBER 2

void addSpace(std::string &strData, int depth)
{
    for(int i = 0; i < depth * SPACE_NUMBER; ++i)
    {
        strData.append(" ");
    }
}

void appendData(std::string &strData, int depth, const std::string &strValue)
{
    addSpace(strData, depth);
    strData.append(strValue);
    strData.append("\n");
}

void appendData(std::string &strData, int depth, const std::string &strName, const std::string &strValue)
{
    addSpace(strData, depth);
    strData.append(strName);
    strData.append(" : ");
    strData.append(strValue);
    strData.append("\n");
}

void serialize_message(const google::protobuf::Message& message, std::string &strData, int depth) {
    const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
    const google::protobuf::Reflection* reflection = message.GetReflection();
    for (int i = 0; i < descriptor->field_count(); ++i) {
        const google::protobuf::FieldDescriptor* field = descriptor->field(i);
        if(!field->is_repeated()){
            if(!reflection->HasField(message, field))
                continue;
            switch (field->cpp_type()) {

#define CASE_FIELD_TYPE(cpptype, method, valuetype, format) \
                case google::protobuf::FieldDescriptor::CPPTYPE_##cpptype:{\
                    valuetype value = reflection->Get##method(message, field);\
                    char buffer[128] = "";\
                    if(google::protobuf::FieldDescriptor::CPPTYPE_##cpptype != google::protobuf::FieldDescriptor::CPPTYPE_BOOL)\
                    {\
                        snprintf(buffer, sizeof(buffer), format, value);\
                    } else\
                    {\
                        snprintf(buffer, sizeof(buffer), format, value?"true":"false");\
                    }\
                    const std::string &strValue = std::string(buffer);\
                    const std::string &strName = field->name();\
                    appendData(strData, depth, strName, strValue);\
                    break;\
                }

                CASE_FIELD_TYPE(INT32, Int32, int32_t, "%d");
                CASE_FIELD_TYPE(UINT32, UInt32, uint32_t, "%u");
                CASE_FIELD_TYPE(INT64, Int64, int64_t, "%lld");
                CASE_FIELD_TYPE(UINT64, UInt64, uint64_t, "%llu");
                CASE_FIELD_TYPE(FLOAT, Float, float, "%f");
                CASE_FIELD_TYPE(DOUBLE, Double, double, "%lf");
                CASE_FIELD_TYPE(BOOL, Bool, bool, "%s");
#undef CASE_FIELD_TYPE

                case google::protobuf::FieldDescriptor::CPPTYPE_ENUM: {
                    const std::string &strValue = reflection->GetEnum(message, field)->name();
                    const std::string &strName = field->name();
                    appendData(strData, depth, strName, strValue);
                    break;
                }
                case google::protobuf::FieldDescriptor::CPPTYPE_STRING: {
                    const std::string &strValue = reflection->GetString(message, field);
                    const std::string &strName = field->name();
                    appendData(strData, depth, strName, "\"" + strValue + "\"");
                    break;
                }
                case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE: {
                    const std::string &strName = field->name();
                    appendData(strData, depth, strName + " {");
                    const google::protobuf::Message& submessage = reflection->GetMessage(message, field);
                    serialize_message(submessage, strData, depth + 1);
                    appendData(strData, depth, "}");
                    break;
                }
            }
        }
        else
        {
               int32  FieldNum = 0;
               for (FieldNum = 0; FieldNum < reflection->FieldSize(message, field); FieldNum++) {
                   switch (field->cpp_type()) {

#define CASE_FIELD_TYPE(cpptype, method, valuetype, format) \
                       case google::protobuf::FieldDescriptor::CPPTYPE_##cpptype:{ \
                            valuetype value = reflection->GetRepeated##method(message, field, FieldNum); \
                            char buffer[128] = "";\
                            if(google::protobuf::FieldDescriptor::CPPTYPE_##cpptype != google::protobuf::FieldDescriptor::CPPTYPE_BOOL)\
                            {\
                                snprintf(buffer, sizeof(buffer), format, value);\
                            } else\
                            {\
                                snprintf(buffer, sizeof(buffer), format, value?"true":"false");\
                            }\
                            const std::string &strValue = std::string(buffer);\
                            const std::string &strName = field->name();\
                            appendData(strData, depth, strName, strValue);\
                            break;\
                       }

                   CASE_FIELD_TYPE(INT32, Int32, int32_t, "%d");
                   CASE_FIELD_TYPE(UINT32, UInt32, uint32_t, "%u");
                   CASE_FIELD_TYPE(INT64, Int64, int64_t, "%lld");
                   CASE_FIELD_TYPE(UINT64, UInt64, uint64_t, "%llu");
                   CASE_FIELD_TYPE(FLOAT, Float, float, "%f");
                   CASE_FIELD_TYPE(DOUBLE, Double, double, "%lf");
                   CASE_FIELD_TYPE(BOOL, Bool, bool, "%s");
#undef CASE_FIELD_TYPE

                       case google::protobuf::FieldDescriptor::CPPTYPE_ENUM: {
                           const std::string &strValue = reflection->GetRepeatedEnum(message, field, FieldNum)->name();
                           const std::string &strName = field->name();
                           appendData(strData, depth, strName, strValue);
                           break;
                       }
                       case google::protobuf::FieldDescriptor::CPPTYPE_STRING: {
                           const std::string &strValue = reflection->GetRepeatedString(message, field, FieldNum);
                           const std::string &strName = field->name();
                           appendData(strData, depth, strName, "\"" + strValue + "\"");
                           break;
                       }
                       case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE: {
                           const std::string &strName = field->name();
                           appendData(strData, depth, strName + " {");
                           const google::protobuf::Message& submessage = reflection->GetRepeatedMessage(message, field, FieldNum);
                           serialize_message(submessage, strData, depth + 1);
                           appendData(strData, depth, "}");
                           break;
                       }
                   }
               }
        }
    }
}

enum EParseMessageType
{
    EPARSEMESSAGETYPE_INIT = 0,
    EPARSEMESSAGETYPE_NODE,
    EPARSEMESSAGETYPE_MESSAGE_START,
    EPARSEMESSAGETYPE_MESSAGE_END,

};

struct TParseNode
{
    EParseMessageType type;
    std::string value;
};

class CParseMessage
{
public:
    CParseMessage(const char *data);
    const char *getData();
    TParseNode *getName();
    TParseNode *getValue();
private:
    TParseNode m_parseName;
    TParseNode m_parseValue;
    const char *m_startData;
    const char *m_endData;
};

CParseMessage::CParseMessage(const char *data):
    m_startData(data),
    m_endData(m_startData + strlen(data))
{
    m_parseName.type = EPARSEMESSAGETYPE_INIT;
    m_parseValue.type = EPARSEMESSAGETYPE_INIT;
}

const char *CParseMessage::getData()
{
    return m_startData;
}

TParseNode *CParseMessage::getName()
{
    m_parseName.type = EPARSEMESSAGETYPE_INIT;
    m_parseName.value.clear();
    bool isName = false;
    const char *currData =  m_startData;
    for(;currData < m_endData; ++currData)
    {
        if(*currData == ' ' || *currData == ' \t' || *currData == '\n' || *currData == '\r')
        {
            if(isName)
            {
                m_parseName.value =  std::string(m_startData, currData - m_startData);
                isName = false;
            }
            ++m_startData;
            continue;
        }
        else if(*currData == '{')
        {
            m_parseName.type = EPARSEMESSAGETYPE_MESSAGE_START;
            break;
        }
        else if(*currData == ':')
        {
            m_parseName.type = EPARSEMESSAGETYPE_NODE;
            break;
        }
        else if(*currData == '}')
        {
            m_parseName.type = EPARSEMESSAGETYPE_MESSAGE_END;
            if(!m_parseName.value.empty())
            {
                printf("error \n");
                return NULL;
            }
            break;
        }
        else
        {
            if(!m_parseName.value.empty())
            {
                printf("error \n");
                return NULL;
            }
            isName = true;
        }
    }

    if(isName)
    {
        m_parseName.value =  std::string(m_startData, currData - m_startData);
        isName = false;
    }
    ++currData;
    m_startData = currData;

    return &m_parseName;
}

TParseNode *CParseMessage::getValue()
{
    m_parseValue.type = EPARSEMESSAGETYPE_INIT;
    m_parseValue.value.clear();
    bool isName = false;
    const char *currData =  m_startData;
    for(;currData < m_endData; ++currData)
    {
        if(*currData == ' ' || *currData == ' \t' || *currData == '\n' || *currData == '\r' || *currData == '"')
        {
            if(isName)
            {
                m_parseValue.value =  std::string(m_startData, currData - m_startData);
                isName = false;
                break;
            }
            ++m_startData;
            continue;
        }
        else
        {
            if(!m_parseValue.value.empty())
            {
                printf("error \n");
                return NULL;
            }
            isName = true;
        }
    }


    ++currData;
    m_startData = currData;

    return &m_parseValue;
}


void parse_message(google::protobuf::Message *message, CParseMessage &parseMessage) {
    const google::protobuf::Descriptor* descriptor = message->GetDescriptor();
    const google::protobuf::Reflection* reflection = message->GetReflection();
    while(true)
    {
        TParseNode *parseName = parseMessage.getName();
        if(!parseName)
        {
            printf("parseName == NULL \n");
            return;
        }

        if(parseName->type == EPARSEMESSAGETYPE_INIT)
        {
            printf("parseName->type == EPARSEMESSAGETYPE_INIT \n");
            return;
        }
        else if(parseName->type == EPARSEMESSAGETYPE_NODE)
        {
            printf("node name = %s \n", parseName->value.c_str());
            const FieldDescriptor *field = descriptor->FindFieldByName(parseName->value);
            if(!field)
            {
                printf("name = %s invalid \n", parseName->value.c_str());
                return;
            }

            TParseNode *parseValue = parseMessage.getValue();
            printf("node value = %s \n", parseValue->value.c_str());



            if(!field->is_repeated())
            {
                switch (field->cpp_type()) {
#define CASE_FIELD_TYPE(cpptype, method, func) \
                        case google::protobuf::FieldDescriptor::CPPTYPE_##cpptype:{ \
                             reflection->method(message, field, func);\
                             break;\
                        }

                    CASE_FIELD_TYPE(INT32, SetInt32, atoll(parseValue->value.c_str()));
                    CASE_FIELD_TYPE(UINT32, SetUInt32, atoll(parseValue->value.c_str()));
                    CASE_FIELD_TYPE(INT64, SetInt64, atoll(parseValue->value.c_str()));
                    CASE_FIELD_TYPE(UINT64, SetUInt64, atoll(parseValue->value.c_str()));
                    CASE_FIELD_TYPE(FLOAT, SetFloat, atof(parseValue->value.c_str()));
                    CASE_FIELD_TYPE(DOUBLE, SetDouble, atof(parseValue->value.c_str()));
                    CASE_FIELD_TYPE(BOOL, SetBool, strcasecmp(parseValue->value.c_str(), "true") == 0 ? true : false);
                    CASE_FIELD_TYPE(ENUM, SetEnum, field->enum_type()->FindValueByName(parseValue->value));
                    CASE_FIELD_TYPE(STRING, SetString, parseValue->value);
 #undef CASE_FIELD_TYPE
                }

                /*
                if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32)
                {
                    reflection->SetInt32(message, field, atoll(parseValue->value.c_str()));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32)
                {
                    reflection->SetUInt32(message, field, atoll(parseValue->value.c_str()));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64)
                {
                    reflection->SetInt64(message, field, atoll(parseValue->value.c_str()));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64)
                {
                    reflection->SetUInt64(message, field, atoll(parseValue->value.c_str()));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE)
                {
                    reflection->SetDouble(message, field, atof(parseValue->value.c_str()));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_FLOAT)
                {
                    reflection->SetFloat(message, field, atof(parseValue->value.c_str()));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_BOOL)
                {
                    reflection->SetBool(message, field, strcasecmp(parseValue->value.c_str(), "true") == 0 ? true : false);
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_ENUM)
                {
                    reflection->SetEnum(message, field, field->enum_type()->FindValueByName(parseValue->value));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING)
                {

                    reflection->SetString(message, field, parseValue->value);
                }
                */
            }
            else
            {
                switch (field->cpp_type()) {
#define CASE_FIELD_TYPE(cpptype, method, func) \
                        case google::protobuf::FieldDescriptor::CPPTYPE_##cpptype:{ \
                             reflection->method(message, field, func);\
                             break;\
                        }

                    CASE_FIELD_TYPE(INT32, AddInt32, atoll(parseValue->value.c_str()));
                    CASE_FIELD_TYPE(UINT32, AddUInt32, atoll(parseValue->value.c_str()));
                    CASE_FIELD_TYPE(INT64, AddInt64, atoll(parseValue->value.c_str()));
                    CASE_FIELD_TYPE(UINT64, AddUInt64, atoll(parseValue->value.c_str()));
                    CASE_FIELD_TYPE(FLOAT, AddFloat, atof(parseValue->value.c_str()));
                    CASE_FIELD_TYPE(DOUBLE, AddDouble, atof(parseValue->value.c_str()));
                    CASE_FIELD_TYPE(BOOL, AddBool, strcasecmp(parseValue->value.c_str(), "true") == 0 ? true : false);
                    CASE_FIELD_TYPE(ENUM, AddEnum, field->enum_type()->FindValueByName(parseValue->value));
                    CASE_FIELD_TYPE(STRING, AddString, parseValue->value);
 #undef CASE_FIELD_TYPE
                }

                /*
                if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32)
                {
                    reflection->AddInt32(message, field, atoll(parseValue->value.c_str()));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32)
                {
                    reflection->AddUInt32(message, field, atoll(parseValue->value.c_str()));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64)
                {
                    reflection->AddInt64(message, field, atoll(parseValue->value.c_str()));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64)
                {
                    reflection->AddUInt64(message, field, atoll(parseValue->value.c_str()));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE)
                {
                    reflection->AddDouble(message, field, atof(parseValue->value.c_str()));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_FLOAT)
                {
                    reflection->AddFloat(message, field, atof(parseValue->value.c_str()));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_BOOL)
                {
                    reflection->AddBool(message, field, strcasecmp(parseValue->value.c_str(), "true") == 0 ? true : false);
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_ENUM)
                {
                    reflection->SetEnum(message, field,field->enum_type()->FindValueByName(parseValue->value));
                }
                else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING)
                {

                    reflection->AddString(message, field, parseValue->value);
                }
                */

            }
        }
        else if(parseName->type == EPARSEMESSAGETYPE_MESSAGE_START)
        {
            printf("message name %s \n", parseName->value.c_str());
            const FieldDescriptor *field = descriptor->FindFieldByName(parseName->value);
            if(!field)
            {
                printf("name = %s invalid \n", parseName->value.c_str());
                return;
            }

            if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE)
            {
                printf("name = %s != CPPTYPE_MESSAGE \n", parseName->value.c_str());
                return;
            }

            if(!field->is_repeated())
            {
                google::protobuf::Message *subMessage = reflection->MutableMessage(message, field, NULL);
                parse_message(subMessage, parseMessage);
            }
            else
            {
                google::protobuf::Message *subMessage = reflection->AddMessage(message, field, NULL);
                parse_message(subMessage, parseMessage);
            }
            printf("end message name %s \n", parseName->value.c_str());
        }
        else if(parseName->type == EPARSEMESSAGETYPE_MESSAGE_END)
        {
            printf("parseName->type == EPARSEMESSAGETYPE_MESSAGE_END \n");
            return;
        }
        else
        {
            printf("parseName->type == NULL \n");
            return;
        }
    }
}


SKP_TEST_ONECE(protobuf, protobuf_test3)
{
    char buffer[1024] = "";

    //获取当前的工作目录，注意：长度必须大于工作目录的长度加一
    char *p = getcwd(buffer , sizeof(buffer));
    printf("p:[%s] size:[%d]  \n" , p , strlen(p));


    const std::string path = "../../../cpp_study/trunk/project_cpp/src/protobuf/";
    std::string fullPath = path + "caffe.proto";

    ASSERT_TRUE(access(fullPath.c_str(), 0) == 0);
    ASSERT_TRUE(access("./proto/caffe.proto", 0) == 0);

    // 准备配置好文件系统
    google::protobuf::compiler::DiskSourceTree sourceTree;
    // 将当前路径映射为项目根目录 ， project_root 仅仅是个名字，你可以你想要的合法名字.
    sourceTree.MapPath("project_root","./");
    // 配置动态编译器.
    google::protobuf::compiler::Importer importer(&sourceTree, NULL);
    // 动态编译proto源文件
    const google::protobuf::FileDescriptor *tFileDescriptor = importer.Import("project_root/proto/caffe.proto");

    ASSERT_TRUE(nullptr != tFileDescriptor);
    // 现在可以从编译器中提取类型的描述信息.
    auto descriptor = importer.pool()->FindMessageTypeByName("caffe.AddressBook");
    ASSERT_TRUE(nullptr != descriptor);

    // 创建一个动态的消息工厂.
    google::protobuf::DynamicMessageFactory factory;
    // 从消息工厂中创建出一个类型原型.
    auto proto = factory.GetPrototype(descriptor);
    // 构造一个可用的消息.
    auto message= proto->New();


    std::string str = \
    "people {\
      name: \"aaa111\"\
      age: 18\
      email: \"qq.com\"\
      phone {\
        number: \"111\"\
        type: MOBILE\
      }\
      phone {\
        number: \"222\"\
        type: HOME\
      }\
      phone {\
        number: \"333\"\
        type: WORK\
      }\
    string_arg5: \"string_arg5\"\
    string_arg5: \"string_arg5\"\
    int32_arg6: 6\
    int32_arg6: 6\
    uint32_arg7: 7\
    int64_arg8: 8\
    uint64_arg9: 9\
    double_arg10: 10.1\
    float_arg11: 11.11\
    bool_arg12: false\
    }\
    people {\
      name: \"bbb111\"\
      age: 18\
      email: \"sina.com\"\
      phone {\
        number: \"a111\"\
        type: MOBILE\
      }\
      phone {\
        number: \"b222\"\
        type: HOME\
      }\
      phone {\
        number: \"c333\"\
        type: WORK\
      }\
    string_arg5: \"string_arg5\"\
    string_arg5: \"string_arg5\"\
    uint32_arg7: 77\
    int64_arg8: 88\
    double_arg10: 100.2\
    float_arg11: 110.22\
    } \
    t1 : \"t1\"\  "
    "t1 : \"t11\"\
    book_name:\"book_name\"\
    ";



    google::protobuf::TextFormat::ParseFromString(str, message);
    printf("*************PrintDebugString****************** \n");
    message->PrintDebugString();


    std::string strData;
    serialize_message(*message, strData, 0);
    printf("*************serialize_message****************** \n");
    printf("%s \n", strData.c_str());
    message->Clear();

    printf("*************parse_message****************** \n");
    CParseMessage parse(strData.c_str());
    parse_message(message, parse);
    printf("*************PrintDebugString****************** \n");
    message->PrintDebugString();

    // 删除消息.
    delete message ;
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
    const Descriptor* descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName("T.Test");
    ASSERT_TRUE(nullptr != descriptor);

    // 利用Descriptor拿到类型注册的instance. 这个是不可修改的.
    const Message* prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
    ASSERT_TRUE(nullptr != prototype);

    // 构造一个可用的消息.
    Message* message = prototype->New();
    // 只有当我们预先编译了test消息并且正确链接才能这么干.
    T::Test *test = dynamic_cast<T::Test*>(message);
    // 直接调用message的具体接口
    // 其实这些接口是语法糖接口.所以并没有对应的反射机制来对应调用.
    // 反射机制实现了的Set/Get XXX系列接口，是属于Reflection的接口，接收Message作为参数.
    test->set_id(1);
    std::cout<<test->Utf8DebugString()<<std::endl;
    delete message ;
}

SKP_TEST(protobuf, protobuf_test4)
{
    // 拿到一个对象，不在乎怎么拿到，可以是通过反射拿到。
    // 这里简单直接的创建一个.
    T::Test p_test ;
    // 拿到对象的描述包.
    const Descriptor* descriptor = p_test.GetDescriptor() ;
    // 拿到对象的反射配置.
    const Reflection* reflecter = p_test.GetReflection() ;
    // 拿到属性的描述包.
    const FieldDescriptor* field = descriptor->FindFieldByName("id");
    // 设置属性的值.
    reflecter->SetInt32(&p_test , field , 5 ) ;
    // 获取属性的值.
    std::cout<<reflecter->GetInt32(p_test , field)<< std::endl ;
}
