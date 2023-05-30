#include "getApi.h"
using namespace std;

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <curl/curl.h>
#include <json/json.h>
#include <fstream>
#include <memory>

std::string client_id = "gAkQtVGjuoNhkoKf3mNvFDCo";
std::string client_secret = "0RpWRe94lQF2VyBuvT2sBfzSjwd582yv";

inline size_t onWriteData(void * buffer, size_t size, size_t nmemb, void * userp)
{
	std::string * str = dynamic_cast<std::string *>((std::string *)userp);
	str->append((char *)buffer, size * nmemb);
	return nmemb;
}

std::string getFileBase64Content(const char * path, bool urlencoded = false)
{
	const std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];
	const unsigned int bufferSize = 1024;
	unsigned char buffer[bufferSize];
	std::ifstream file_read;
	file_read.open(path, std::ios::binary);
	while (!file_read.eof())
	{
		file_read.read((char *)buffer, bufferSize * sizeof(char));
		int num = file_read.gcount();
		int m = 0;
		while (num--)
		{
			char_array_3[i++] = buffer[m++];
			if (i == 3)
			{
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;
				for (i = 0; (i < 4); i++)
				{
					ret += base64_chars[char_array_4[i]];
				}
				i = 0;
			}
		}
	}
	file_read.close();
	if (i)
	{
		for (j = i; j < 3; j++)
		{
			char_array_3[j] = '\0';
		}

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;
		for (j = 0; (j < i + 1); j++)
		{
			ret += base64_chars[char_array_4[j]];
		}
		while ((i++ < 3))
		{
			ret += '=';
		}
	}
	if (urlencoded)
	{
		ret = curl_escape(ret.c_str(), ret.length());
	}
	return ret;
}


std::string getAccessToken()
{
	std::string result;
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_URL, "https://aip.baidubce.com/oauth/2.0/token");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
		headers = curl_slist_append(headers, "Accept: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		std::string data = "grant_type=client_credentials&client_id=" + client_id + "&client_secret=" + client_secret;
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteData);
		res = curl_easy_perform(curl);
	}
	curl_easy_cleanup(curl);
	Json::Value obj;
	std::string error;
	Json::CharReaderBuilder crbuilder;
	std::unique_ptr<Json::CharReader> reader(crbuilder.newCharReader());
	reader->parse(result.data(), result.data() + result.size(), &obj, &error);
	return obj["access_token"].asString();
}

int getApi::getInfo(const char * path)
{
	std::string result;
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_URL, ("https://aip.baidubce.com/rest/2.0/ocr/v1/handwriting?access_token=" + getAccessToken()).c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
		headers = curl_slist_append(headers, "Accept: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		// image ����ͨ�� getFileBase64Content('C:\fakepath\31ed.jpg') ������ȡ
		// ע��getFileBase64Content�����ڶ������������Content-Type��application/x-www-form-urlencodedʱ��urlencoded������ΪTrue

		const char *data = ("image=" + getFileBase64Content(path, true)).c_str();
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteData);
		res = curl_easy_perform(curl);
		std::cout << result;
	}
	curl_easy_cleanup(curl);
	return (int)res;
	
}
