#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include <rapidjson/istreamwrapper.h>
#include <iostream>
#include <fstream>
#include "testJson.h"

using namespace rapidjson;
using namespace std;

void jsonTest::testCall() {
    ifstream ifs("путь до джисонки");          //чтение джисонки
    IStreamWrapper isw(ifs);

    Document doc;                       //инициализация
    doc.ParseStream(isw);
    assert(doc.IsObject());


    if (doc.IsObject()) {                 //проверка на объект (крч, прочитало или нет); можно и без if делать впринципе
        assert(doc.HasMember("hello"));         //поиск значения переменной
        assert(doc["hello"].IsString());
        cout << doc["hello"].GetString();
    }

    /*if (doc.ParseStream(isw).HasParseError()) {           //проверка на ошибку
        fprintf(stderr, "\nError(offset %u): %s\n",
            (unsigned)doc.GetErrorOffset(),
            GetParseError_En(doc.GetParseError()));
    }*/
}