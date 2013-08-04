//
//  OBEncrytionUtil.h
//  AirCommander
//
//  Created by OwenTsang on 7/18/13.
//
//

#ifndef __OBEncrytionUtil_h
#define __OBEncrytionUtil_h

#include "cocos2d.h"

class EncrytionUtil
{
public:
	static int Encryt(std::string& stream, const char* secret = "Cocos2dxReallyHelpUs")
	{
		return Encryt(stream, 0,  stream.length()-1, secret);
	}
    
	static int Decrpt(std::string& stream, const char* secret = "Cocos2dxReallyHelpUs")
	{
		return Decrpt(stream, 0, stream.length()-1, secret);
	}
    
	static int Encryt(std::string& stream, int begin, int end, const char* secret)
	{
		return XORM(stream, begin, end, secret);
	}
    
	static int Decrpt(std::string& stream, int begin, int end, const char* secret)
	{
		return XORM(stream, begin, end, secret);
	}
	
private:
	static int XORM(std::string& stream, int begin, int end, const char* secret)
	{
        if (begin<0 || end>=stream.length() || begin>end || strlen(secret) == 0)
        {
            return -1;
        }
        
        int keyLength = strlen(secret);
        int j(0);
        for (int i=begin; i<=end; i++)
        {
            if (j>=keyLength)
            {
                j = 0;
            } 
            stream[i] = stream[i] ^ secret[j];
            if(stream[i] == '\0')
            {
                stream[i] = secret[j];
            }
            j++;
        }

		return 0;
	}
};

class UserEncrytionUtil
{
public:
    static void setStringForKey(cocos2d::CCUserDefault* encoder,const char* key, const char* value,const char* secret = "Cocos2dxReallyHelpUs")
    {
        if (encoder)
        {
            std::string keyString = key;
            EncrytionUtil::Encryt(keyString,secret);
            
            std::string valueString = value;
            EncrytionUtil::Encryt(valueString,secret);
            
            CCLOG("before Encrytion: %s >> after Encrytion: %s",value,valueString.c_str());
            encoder->setStringForKey(keyString.c_str(), valueString);
            encoder->flush();
        }
    }
    
    static void setIntegerForKey(cocos2d::CCUserDefault* encoder,const char* key, int value,const char* secret = "Cocos2dxReallyHelpUs")
    {
        char valueString[64] = {0};
        sprintf(valueString, "%d",value);
        setStringForKey(encoder,key,valueString,secret);
    }
    
    static std::string getStringForKey(cocos2d::CCUserDefault* decoder,const char* key, const char* secret = "Cocos2dxReallyHelpUs")
    {
        if (decoder)
        {
            std::string keyString = key;
            EncrytionUtil::Encryt(keyString,secret);
            
            std::string valueString = decoder->getStringForKey(keyString.c_str());
            CCLOG("get string from XML: %s", valueString.c_str());
            EncrytionUtil::Decrpt(valueString,secret);
            CCLOG("after Decrption : %s",valueString.c_str());
            return valueString;
        }
        return "";
    }
    
    static int getIntegerForKey(cocos2d::CCUserDefault* decoder,const char* key,const char* secret = "Cocos2dxReallyHelpUs")
    {
        return  atoi(getStringForKey(decoder,key,secret).c_str());
    }
};


#endif
