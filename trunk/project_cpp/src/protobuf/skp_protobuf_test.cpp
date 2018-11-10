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
#include "google/protobuf/text_format.h"
#include "caffe.pb.h"

using namespace std;
using namespace google::protobuf;
using namespace caffe;

SKP_TEST(protobuf, protobuf_test1)
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

    book.add_t1("t1");
    book.add_t1("t11");
    book.add_t2(2);
    book.add_t2(22);

    printf("**************PrintDebugString***************** \n");
    book.PrintDebugString();


    std::string output1;
    ASSERT_TRUE(book.SerializeToString(&output1));
    printf("************SerializeToString******************* \n");
    printf("%s \n", output1.c_str());

    std::string output2;
    ASSERT_TRUE(google::protobuf::TextFormat::PrintToString(book, &output2));
    printf("*************PrintToString****************** \n");
    printf("%s \n", output2.c_str());
    log_print("%s \n", output2.c_str());

    AddressBook book2;
    ASSERT_TRUE(google::protobuf::TextFormat::ParseFromString(output2, &book2));
    printf("*************ParseFromString****************** \n");
    book2.PrintDebugString();
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

bool serialize_message(const google::protobuf::Message& message, std::string &strData, int depth) {
    const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
    assert(descriptor != NULL);
    const google::protobuf::Reflection* reflection = message.GetReflection();
    assert(reflection != NULL);
    for (int i = 0; i < descriptor->field_count(); ++i) {
        const google::protobuf::FieldDescriptor* field = descriptor->field(i);
        assert(field != NULL);
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

    return true;
}

enum EParseMessageType
{
    EPARSEMESSAGETYPE_ERROR = 0,
    EPARSEMESSAGETYPE_NODE,
    EPARSEMESSAGETYPE_MESSAGE_BEGIN,
    EPARSEMESSAGETYPE_MESSAGE_END,
    EPARSEMESSAGETYPE_FINISH,
};

class CParseMessage;

struct CParseMessageKey
{
    friend class CParseMessage;
public:
    CParseMessageKey()
    {
        clear();
    }

//    EParseMessageType getType()
//    {
//        return m_type;
//    }

    const std::string &getValue()
    {
        return m_strValue;
    }

    bool isError()
    {
        return m_type == EPARSEMESSAGETYPE_ERROR;
    }


    bool isNode()
    {
        return m_type == EPARSEMESSAGETYPE_NODE;
    }

    bool isMessageBegin()
    {
        return m_type == EPARSEMESSAGETYPE_MESSAGE_BEGIN;
    }

    bool isMessageEnd()
    {
        return m_type == EPARSEMESSAGETYPE_MESSAGE_END;
    }

    bool isFinish()
    {
        return m_type == EPARSEMESSAGETYPE_FINISH;
    }

    const std::string &getError()
    {
        return m_strError;
    }
protected:
    void clear()
    {
        m_type = EPARSEMESSAGETYPE_ERROR;
        m_strValue.clear();
        m_strType.clear();
        m_strError.clear();
    }

private:
    EParseMessageType m_type;
    std::string m_strValue;
    std::string m_strType;
    std::string m_strError;
};


class CParseMessage
{
public:
    CParseMessage(const char *data);
    CParseMessageKey &getKey();
    const std::string &getValue();
    const std::string getError()
    {
        return std::string(m_startData, m_currData - m_startData);
    }

protected:
    void getType();

    bool isFinish()
    {
        return m_currData >= m_endData;
    }

    void setError()
    {
        m_strKeyCache.m_type = EPARSEMESSAGETYPE_ERROR;
        m_strKeyCache.m_strError = getError();
        printf("%s \n", m_strKeyCache.m_strError.c_str());
    }

private:
    const char *m_startData;
    const char *m_currData;
    const char *m_endData;
    CParseMessageKey m_strKeyCache;
    std::string m_strValueCache;
};




CParseMessage::CParseMessage(const char *data):
    m_startData(data),
    m_currData(m_startData),
    m_endData(m_startData + strlen(data))
{
}

CParseMessageKey &CParseMessage::getKey()
{
    //[name{}]
    //[ name{}]
    //[name {}]
    //[ name {}]
    //[name:]
    //[ name:]
    //[name :]
    //[ name:]

    m_strKeyCache.clear();
    const char *currData =  m_currData;
    for(;currData < m_endData; ++currData)
    {
        if(*currData == ' ' || *currData == ' \t' || *currData == '\n' || *currData == '\r')
        {
            if(!m_strKeyCache.m_strValue.empty())
                break;
            continue;
        }
        else if(*currData == '{')
        {
            break;
        }
        else if(*currData == ':')
        {
            break;
        }
        else if(*currData == '}')
        {
            break;
        }
        else
        {

            m_strKeyCache.m_strValue += *currData;
        }
    }

    m_currData = currData;

    if(isFinish() && m_strKeyCache.m_strValue.empty())
    {
        m_strKeyCache.m_type = EPARSEMESSAGETYPE_FINISH;
        return m_strKeyCache;
    }

    if(isFinish() && !m_strKeyCache.m_strValue.empty())
    {
        printf("error : key != empty && parse finish \n");
        setError();
        return m_strKeyCache;
    }

    getType();
    if(m_strKeyCache.m_strValue.empty() && m_strKeyCache.m_type != EPARSEMESSAGETYPE_MESSAGE_END)
    {
        printf("error : key == empty \n");
        setError();
        return m_strKeyCache;
    }

    return m_strKeyCache;
}

void CParseMessage::getType()
{
    m_strKeyCache.m_type = EPARSEMESSAGETYPE_ERROR;
    m_strKeyCache.m_strType.clear();
    const char *currData =  m_currData;
    for(;currData < m_endData; ++currData)
    {
        if(*currData == ' ' || *currData == ' \t' || *currData == '\n' || *currData == '\r')
        {
            if(!m_strKeyCache.m_strType.empty())
                break;
            continue;
        }
        else if(*currData == '{')
        {
            m_strKeyCache.m_type =  EPARSEMESSAGETYPE_MESSAGE_BEGIN;
            break;
        }
        else if(*currData == ':')
        {
            m_strKeyCache.m_type = EPARSEMESSAGETYPE_NODE;
            break;
        }
        else if(*currData == '}')
        {
            m_strKeyCache.m_type = EPARSEMESSAGETYPE_MESSAGE_END;
            break;
        }
        else
        {
            m_strKeyCache.m_strType += *currData;
        }
    }
    m_currData = ++currData;

    if(!m_strKeyCache.m_strType.empty())
    {
        printf("error : getType error = [%s] \n", m_strKeyCache.m_strType.c_str());
        setError();
        return;
    }

    if(isFinish())
    {
        printf("error : getType empty && parse finish \n");
        setError();
        return;
    }

    if(EPARSEMESSAGETYPE_ERROR == m_strKeyCache.m_type && m_strKeyCache.m_strType.empty())
    {
        printf("error : getType empty \n");
        setError();
        return;
    }
}

const std::string &CParseMessage::getValue()
{
    m_strValueCache.clear();
    const char *currData =  m_currData;
    for(;currData < m_endData; ++currData)
    {
        if(*currData == ' ' || *currData == ' \t' || *currData == '\n'
                || *currData == '\r' || *currData == '"' ||  *currData == '{' ||
                *currData == ':'||  *currData == '}')
        {
            if(!m_strValueCache.empty())
            {
                if(*currData == '"')
                    ++currData;
                break;
            }

            continue;
        }
        else
        {
            m_strValueCache += *currData;
        }
    }

    m_currData = currData;

    if(m_strValueCache.empty())
    {
        printf("error : getValue empty \n");
        printf("%s \n", getError().c_str());
    }

    return m_strValueCache;
}

bool parse_message(google::protobuf::Message *message, CParseMessage &parseMessage) {
    const google::protobuf::Descriptor* descriptor = message->GetDescriptor();
    assert(descriptor != NULL);
    const google::protobuf::Reflection* reflection = message->GetReflection();
    assert(reflection != NULL);
    while(true)
    {
        CParseMessageKey &key =  parseMessage.getKey();
        if(key.isFinish())
            return true;
        else if(key.isError())
            return false;
        else if(key.isNode())
        {
            const FieldDescriptor *field = descriptor->FindFieldByName(key.getValue());
            assert(field != NULL);

            const std::string &value = parseMessage.getValue();
            assert(!value.empty());

            if(!field->is_repeated())
            {
                switch (field->cpp_type()) {
#define CASE_FIELD_TYPE(cpptype, method, func) \
                        case google::protobuf::FieldDescriptor::CPPTYPE_##cpptype:{ \
                             reflection->method(message, field, func);\
                             break;\
                        }

                    CASE_FIELD_TYPE(INT32, SetInt32, atoll(value.c_str()));
                    CASE_FIELD_TYPE(UINT32, SetUInt32, atoll(value.c_str()));
                    CASE_FIELD_TYPE(INT64, SetInt64, atoll(value.c_str()));
                    CASE_FIELD_TYPE(UINT64, SetUInt64, atoll(value.c_str()));
                    CASE_FIELD_TYPE(FLOAT, SetFloat, atof(value.c_str()));
                    CASE_FIELD_TYPE(DOUBLE, SetDouble, atof(value.c_str()));
                    CASE_FIELD_TYPE(BOOL, SetBool, strcasecmp(value.c_str(), "true") == 0 ? true : false);
                    CASE_FIELD_TYPE(ENUM, SetEnum, field->enum_type()->FindValueByName(value));
                    CASE_FIELD_TYPE(STRING, SetString, value);
 #undef CASE_FIELD_TYPE
                }
            }
            else
            {
                switch (field->cpp_type()) {
#define CASE_FIELD_TYPE(cpptype, method, func) \
                        case google::protobuf::FieldDescriptor::CPPTYPE_##cpptype:{ \
                             reflection->method(message, field, func);\
                             break;\
                        }

                    CASE_FIELD_TYPE(INT32, AddInt32, atoll(value.c_str()));
                    CASE_FIELD_TYPE(UINT32, AddUInt32, atoll(value.c_str()));
                    CASE_FIELD_TYPE(INT64, AddInt64, atoll(value.c_str()));
                    CASE_FIELD_TYPE(UINT64, AddUInt64, atoll(value.c_str()));
                    CASE_FIELD_TYPE(FLOAT, AddFloat, atof(value.c_str()));
                    CASE_FIELD_TYPE(DOUBLE, AddDouble, atof(value.c_str()));
                    CASE_FIELD_TYPE(BOOL, AddBool, strcasecmp(value.c_str(), "true") == 0 ? true : false);
                    CASE_FIELD_TYPE(ENUM, AddEnum, field->enum_type()->FindValueByName(value));
                    CASE_FIELD_TYPE(STRING, AddString, value);
 #undef CASE_FIELD_TYPE
                }
            }
        }
        else if(key.isMessageBegin())
        {
            const FieldDescriptor *field = descriptor->FindFieldByName(key.getValue());
            assert(field != NULL);
            assert(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE);

            if(!field->is_repeated())
            {
                google::protobuf::Message *subMessage = reflection->MutableMessage(message, field, NULL);
                assert(subMessage != NULL);
                if(!parse_message(subMessage, parseMessage))
                    return false;
            }
            else
            {
                google::protobuf::Message *subMessage = reflection->AddMessage(message, field, NULL);
                assert(subMessage != NULL);
                if(!parse_message(subMessage, parseMessage))
                    return false;
            }
        }
        else if(key.isMessageEnd())
        {
            return true;
        }
        else
        {
            assert(false);
        }
    }

    return true;
}


SKP_TEST(protobuf, protobuf_test3)
{
    char buffer[1024] = "";

    //获取当前的工作目录，注意：长度必须大于工作目录的长度加一
    char *p = getcwd(buffer , sizeof(buffer));
    printf("p:[%s] size:[%d]  \n" , p , strlen(p));


    const std::string path = "../../../cpp_study/trunk/project_cpp/src/protobuf/";
    std::string fullPath = path + "caffe.proto";

    ASSERT_TRUE(access(fullPath.c_str(), 0) == 0);
    ASSERT_TRUE(access("./proto/caffe.proto", 0) == 0);



//    // 准备配置好文件系统
//    google::protobuf::compiler::DiskSourceTree sourceTree;
//    // 将当前路径映射为项目根目录 ， project_root 仅仅是个名字，你可以你想要的合法名字.
//    sourceTree.MapPath("project_root","./");
//    // 配置动态编译器.
//    google::protobuf::compiler::Importer importer(&sourceTree, NULL);
//    // 动态编译proto源文件
//    const google::protobuf::FileDescriptor *tFileDescriptor = importer.Import("project_root/proto/caffe.proto");


//    // 准备配置好文件系统
//    google::protobuf::compiler::DiskSourceTree sourceTree;
//    // 将当前路径映射为项目根目录 ， project_root 仅仅是个名字，你可以你想要的合法名字.
//    sourceTree.MapPath("","./");
//    // 配置动态编译器.
//    google::protobuf::compiler::Importer importer(&sourceTree, NULL);
//    // 动态编译proto源文件
//    const google::protobuf::FileDescriptor *tFileDescriptor = importer.Import("proto/caffe.proto");


    // 准备配置好文件系统
    google::protobuf::compiler::DiskSourceTree sourceTree;
    // 将当前路径映射为项目根目录 ， project_root 仅仅是个名字，你可以你想要的合法名字.
    sourceTree.MapPath("",path);
    // 配置动态编译器.
    google::protobuf::compiler::Importer importer(&sourceTree, NULL);
    // 动态编译proto源文件
    const google::protobuf::FileDescriptor *tFileDescriptor = importer.Import("caffe.proto");


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
    string_arg5: \"string_arg55\"\
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
    string_arg5: \"string_arg555\"\
    string_arg5: \"string_arg5555\"\
    uint32_arg7: 77\
    int64_arg8: 88\
    double_arg10: 100.2\
    float_arg11: 110.22\
    } \
    t1 : \"t1\"\  "
    "t1 : \"t11\"\
    book_name:\"book_name\"\
    ";



    printf("*************ParseFromString****************** \n");
    ASSERT_TRUE(google::protobuf::TextFormat::ParseFromString(str, message));
    printf("*************PrintDebugString****************** \n");
    message->PrintDebugString();


    printf("*************serialize_message****************** \n");
    std::string strData;
    ASSERT_TRUE(serialize_message(*message, strData, 0));
    printf("%s \n", strData.c_str());
    message->Clear();

    printf("*************parse_message****************** \n");
    CParseMessage parse(strData.c_str());
    ASSERT_TRUE(parse_message(message, parse));
    printf("*************PrintDebugString****************** \n");
    message->PrintDebugString();


        std::string str2 = \
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
        string_arg5: \"string_arg55\"\
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
        string_arg5: \"string_arg555\" abc\
        string_arg5: \"string_arg5555\"\
        uint32_arg7: 77\
        int64_arg8: 88\
        double_arg10: 100.2\
        float_arg11: 110.22\
        } \
        t1 : \"t1\"\  "
        "t1 : \"t11\"\
        book_name:\"book_name\"\
        ";


        printf("*************parse_message error test****************** \n");
        message->Clear();
        CParseMessage parse2(str2.c_str());
        ASSERT_TRUE(!parse_message(message, parse2));
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


SKP_TEST(protobuf, protobuf_test5)
{
    T::Test tTest;
    std::string type_name = tTest.descriptor()->full_name();
    //std::string type_name = "T.Test";
    // 先获得类型的Descriptor .
    const Descriptor* descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
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


#include "importerBase.pb.h"
#include "importer.pb.h"


SKP_TEST(protobuf, protobuf_test6)
{

    importer::AddressBook2 book;

    importerBase::Person2 *people1 = book.add_people();
    people1->set_name("aaa");
    people1->set_age(18);
    people1->set_email("qq.com");

    importerBase::Person2_PhoneNumber *phone1 = people1->add_phone();
    phone1->set_number("111");
    phone1->set_type(::importerBase::Person2_PhoneType_MOBILE);

    importerBase::Person2_PhoneNumber *phone2 = people1->add_phone();
    phone2->set_number("222");
    phone2->set_type(::importerBase::Person2_PhoneType_HOME);

    importerBase::Person2_PhoneNumber *phone3 = people1->add_phone();
    phone3->set_number("333");
    phone3->set_type(::importerBase::Person2_PhoneType_WORK);

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


    importerBase::Person2 *people2 = book.add_people();
    people2->set_name("bbb");
    people2->set_age(18);
    people2->set_email("sina.com");

    importerBase::Person2_PhoneNumber *phone11 = people2->add_phone();
    phone11->set_number("a111");
    phone11->set_type(::importerBase::Person2_PhoneType_MOBILE);

    importerBase::Person2_PhoneNumber *phone22 = people2->add_phone();
    phone22->set_number("b222");
    phone22->set_type(::importerBase::Person2_PhoneType_HOME);

    importerBase::Person2_PhoneNumber *phone33 = people2->add_phone();
    phone33->set_number("c333");
    phone33->set_type(::importerBase::Person2_PhoneType_WORK);

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

    book.add_t1("t1");
    book.add_t1("t11");
    book.add_t2(2);
    book.add_t2(22);

    printf("**************PrintDebugString***************** \n");
    book.PrintDebugString();


    std::string output1;
    ASSERT_TRUE(book.SerializeToString(&output1));
    printf("************SerializeToString******************* \n");
    printf("%s \n", output1.c_str());

    std::string output2;
    ASSERT_TRUE(google::protobuf::TextFormat::PrintToString(book, &output2));
    printf("*************PrintToString****************** \n");
    printf("%s \n", output2.c_str());
    log_print("%s \n", output2.c_str());

    importer::AddressBook2 book2;
    ASSERT_TRUE(google::protobuf::TextFormat::ParseFromString(output2, &book2));
    printf("*************ParseFromString****************** \n");
    book2.PrintDebugString();
}


SKP_TEST(protobuf, protobuf_test7)
{
    char buffer[1024] = "";

    //获取当前的工作目录，注意：长度必须大于工作目录的长度加一
    char *p = getcwd(buffer , sizeof(buffer));
    printf("p:[%s] size:[%d]  \n" , p , strlen(p));


    const std::string path = "../../../cpp_study/trunk/project_cpp/src/protobuf/";
    std::string fullPath = path + "importer.proto";

    ASSERT_TRUE(access(fullPath.c_str(), 0) == 0);



//    // 准备配置好文件系统
//    google::protobuf::compiler::DiskSourceTree sourceTree;
//    // 将当前路径映射为项目根目录 ， project_root 仅仅是个名字，你可以你想要的合法名字.
//    sourceTree.MapPath("project_root","./");
//    // 配置动态编译器.
//    google::protobuf::compiler::Importer importer(&sourceTree, NULL);
//    // 动态编译proto源文件
//    const google::protobuf::FileDescriptor *tFileDescriptor = importer.Import("project_root/proto/importer.proto");


//    // 准备配置好文件系统
//    google::protobuf::compiler::DiskSourceTree sourceTree;
//    // 将当前路径映射为项目根目录 ， project_root 仅仅是个名字，你可以你想要的合法名字.
//    sourceTree.MapPath("","./");
//    // 配置动态编译器.
//    google::protobuf::compiler::Importer importer(&sourceTree, NULL);
//    // 动态编译proto源文件
//    const google::protobuf::FileDescriptor *tFileDescriptor = importer.Import("proto/importer.proto");


    // 准备配置好文件系统
    google::protobuf::compiler::DiskSourceTree sourceTree;
    // 将当前路径映射为项目根目录 ， project_root 仅仅是个名字，你可以你想要的合法名字.
    sourceTree.MapPath("",path);
    // 配置动态编译器.
    google::protobuf::compiler::Importer importer(&sourceTree, NULL);
    // 动态编译proto源文件
    const google::protobuf::FileDescriptor *tFileDescriptor = importer.Import("importer.proto");


    ASSERT_TRUE(nullptr != tFileDescriptor);
    // 现在可以从编译器中提取类型的描述信息.
    auto descriptor = importer.pool()->FindMessageTypeByName("importer.AddressBook2");
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
    string_arg5: \"string_arg55\"\
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
    string_arg5: \"string_arg555\"\
    string_arg5: \"string_arg5555\"\
    uint32_arg7: 77\
    int64_arg8: 88\
    double_arg10: 100.2\
    float_arg11: 110.22\
    } \
    t1 : \"t1\"\  "
    "t1 : \"t11\"\
    book_name:\"book_name\"\
    ";



    printf("*************ParseFromString****************** \n");
    ASSERT_TRUE(google::protobuf::TextFormat::ParseFromString(str, message));
    printf("*************PrintDebugString****************** \n");
    message->PrintDebugString();


    printf("*************serialize_message****************** \n");
    std::string strData;
    ASSERT_TRUE(serialize_message(*message, strData, 0));
    printf("%s \n", strData.c_str());
    message->Clear();

    printf("*************parse_message****************** \n");
    CParseMessage parse(strData.c_str());
    ASSERT_TRUE(parse_message(message, parse));
    printf("*************PrintDebugString****************** \n");
    message->PrintDebugString();


        std::string str2 = \
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
        string_arg5: \"string_arg55\"\
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
        string_arg5: \"string_arg555\" abc\
        string_arg5: \"string_arg5555\"\
        uint32_arg7: 77\
        int64_arg8: 88\
        double_arg10: 100.2\
        float_arg11: 110.22\
        } \
        t1 : \"t1\"\  "
        "t1 : \"t11\"\
        book_name:\"book_name\"\
        ";


        printf("*************parse_message error test****************** \n");
        message->Clear();
        CParseMessage parse2(str2.c_str());
        ASSERT_TRUE(!parse_message(message, parse2));
        printf("*************PrintDebugString****************** \n");
        message->PrintDebugString();


    // 删除消息.
    delete message ;
}
