#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include <rapidjson/istreamwrapper.h>
#include <iostream>
#include <fstream>
#include "testJson.h"

using namespace rapidjson;
using namespace std;

void jsonTest::testCall() {
    ifstream ifs("���� �� ��������");          //������ ��������
    IStreamWrapper isw(ifs);

    Document doc;                       //�������������
    doc.ParseStream(isw);
    assert(doc.IsObject());


    if (doc.IsObject()) {                 //�������� �� ������ (���, ��������� ��� ���); ����� � ��� if ������ ���������
        assert(doc.HasMember("hello"));         //����� �������� ����������
        assert(doc["hello"].IsString());
        cout << doc["hello"].GetString();
    }

    /*if (doc.ParseStream(isw).HasParseError()) {           //�������� �� ������
        fprintf(stderr, "\nError(offset %u): %s\n",
            (unsigned)doc.GetErrorOffset(),
            GetParseError_En(doc.GetParseError()));
    }*/
}