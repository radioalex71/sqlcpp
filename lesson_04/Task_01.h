#pragma once
#pragma execution_character_set("utf-8")
#include "Windows.h"
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <vector>
#include <codecvt>


struct Client
{
	std::string name_;
	std::string surname_;
	std::string email_;
	std::vector<std::string> phones_;
};
class DataBase
{
private:
	pqxx::connection connection_;

public:
	DataBase(const std::string& connection);
	void dropTable();
	void createTable();
	void addClient(const std::string& name, const std::string& surname, const std::string& email, const std::string& phone);
	void addPhone(const std::string& name, const std::string& phone);
	void changeClient(const std::string& email, const std::string& newName, const std::string& newSurname, const std::string& newEmail);
	void deletePhone(const std::string& email, const std::string& phone);
	void deleteClient(const std::string& name);
	std::vector<Client> findClient(const std::string& query);

	void showTable();

};
