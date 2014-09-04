//
//  CCJSONConverter.cpp
//  cocos2d-x-jc
//
//  Created by LIN BOYU on 11/14/12.
//
//

#include "CCJSONConverter.h"

static CCJSONConverter _sharedConverter;

CCJSONConverter * CCJSONConverter::sharedConverter()
{
    static bool firstUse = true;
    if (firstUse)
    {
        firstUse = false;
    }
    return &_sharedConverter;
}

char * CCJSONConverter::strFrom(Dictionary *dictionary)
{
    CCAssert(dictionary, "CCJSONConverter:can not convert a null pointer");
    cJSON * json = cJSON_CreateObject();
    convertDictionaryToJson(dictionary, json);
    char* returnStr = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);
    return returnStr;
}

Dictionary * CCJSONConverter::dictionaryFrom(const char *str)
{
    cJSON * json = cJSON_Parse(str);
    if (!json || json->type!=cJSON_Object) {
        if (json) {
            cJSON_Delete(json);
        }
        return NULL;
    }
    CCAssert(json && json->type==cJSON_Object, "CCJSONConverter:wrong json format");
    Dictionary * dictionary = new Dictionary();
    convertJsonToDictionary(json, dictionary);
    cJSON_Delete(json);
    return dictionary;
}

void CCJSONConverter::convertJsonToDictionary(cJSON *json, Dictionary *dictionary)
{
    dictionary->removeAllObjects();
    cJSON * j = json->child;
    while (j) {
        CCObject * obj = getJsonObj(j);
        dictionary->setObject(obj, j->string);
        j = j->next;
    }
}

void CCJSONConverter::convertDictionaryToJson(Dictionary *dictionary, cJSON *json)
{
#if COCOS2D_VERSION >= 0x00030000
    DictElement * pElement = NULL;
#else
    CCDictElement * pElement = NULL;
#endif
    CCDICT_FOREACH(dictionary, pElement){
        CCObject * obj = pElement->getObject();
        cJSON * jsonItem = getObjJson(obj);
        cJSON_AddItemToObject(json, pElement->getStrKey(), jsonItem);
    }
}

void CCJSONConverter::convertJsonToArray(cJSON * json, CCArray * array)
{
    array->removeAllObjects();
    int size = cJSON_GetArraySize(json);
    for (int i=0; i<size; i++) {
        cJSON * jsonItem = cJSON_GetArrayItem(json, i);
        CCObject * objItem = getJsonObj(jsonItem);
        array->addObject(objItem);
    }
}

void CCJSONConverter::convertArrayToJson(CCArray * array, cJSON * json)
{
    CCObject * obj = NULL;
    CCARRAY_FOREACH(array, obj){
        cJSON * jsonItem = getObjJson(obj);
        cJSON_AddItemToArray(json, jsonItem);
    }
}

cJSON * CCJSONConverter::getObjJson(CCObject * obj)
{
    std::string s = typeid(*obj).name();
    if(s.find("Dictionary")!=std::string::npos){
        cJSON * json = cJSON_CreateObject();
        convertDictionaryToJson((Dictionary *)obj, json);
        return json;
    }else if(s.find("Array")!=std::string::npos){
        cJSON * json = cJSON_CreateArray();
        convertArrayToJson((CCArray *)obj, json);
        return json;
    }else if(s.find("String")!=std::string::npos){
        String * s = (String *)obj;
        cJSON * json = cJSON_CreateString(s->getCString());
        return json;
    }else if(s.find("CCNumber")!=std::string::npos){
        CCNumber * n = (CCNumber *)obj;
        cJSON * json = cJSON_CreateNumber(n->getDoubleValue());
        return json;
    }else if(s.find("CCNull")!=std::string::npos){
        cJSON * json = cJSON_CreateNull();
        return json;
    }
    CCLog("CCJSONConverter encountered an unrecognized type");
    return NULL;
}

CCObject * CCJSONConverter::getJsonObj(cJSON * json)
{
    switch (json->type) {
        case cJSON_Object:
        {
            Dictionary * dictionary = new Dictionary();
            convertJsonToDictionary(json, dictionary);
            return dictionary;
        }
        case cJSON_Array:
        {
            Array * array = new Array();
            convertJsonToArray(json, array);
            return array;
        }
        case cJSON_String:
        {
            String * string = new String(json->valuestring);
            return string;
        }
        case cJSON_Number:
        {
            CCNumber * number = new CCNumber(json->valuedouble);
            return number;
        }
        case cJSON_True:
        {
            CCNumber * boolean = new CCNumber(1);
            return boolean;
        }
        case cJSON_False:
        {
            CCNumber * boolean = new CCNumber(0);
            return boolean;
        }
        case cJSON_NULL:
        {
            CCNull * null = new CCNull();
            return null;
        }
        default:
        {
            CCLog("CCJSONConverter encountered an unrecognized type");
            return NULL;
        }
    }
}
