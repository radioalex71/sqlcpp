#include "Task_01.h"
#include <iostream>
#include <string>

DataBase::DataBase(const std::string& connection) : connection_(connection)
{
    std::cout << "Connection is successful!" << std::endl;
};

void DataBase::dropTable()
{
    pqxx::work trn(connection_);
    trn.exec(R"(DROP TABLE IF EXISTS person, phone)");
    trn.commit();
}

void DataBase::createTable()
{
        pqxx::work txn(connection_);
        pqxx::result r = 
        txn.exec(R"(CREATE TABLE IF NOT EXISTS person (id SERIAL PRIMARY KEY, name VARCHAR(50), surname VARCHAR(50), email VARCHAR(100));
                  CREATE TABLE IF NOT EXISTS phone (id SERIAL PRIMARY KEY, phone_number VARCHAR(20), person_id INTEGER REFERENCES person(id));)");
        txn.commit();
        if (r.empty())
        {
            std::cout << "Table created successfully!" << std::endl;
        }
        else
        {
            throw std::string{"Failed to create table!" };
        }
}

void DataBase::addClient(const std::string& name, const std::string& surname, const std::string& email, const std::string& phone)
{
    pqxx::work txn(connection_);
    pqxx::result r = txn.exec_params(
    "INSERT INTO person (name, surname, email) VALUES ($1, $2, $3)"
    "RETURNING id ", name, surname, email);
    if (!r.empty())
    {
    int person_id = r[0][0].as<int>();
    txn.exec_params(
        "INSERT INTO phone (phone_number, person_id) VALUES ($1, $2)", phone, person_id);
    txn.commit();
    std::cout << "Client added with id: " << person_id << std::endl;
    }
    else
    {
    txn.abort();
    throw std::string{ "Failed to add client!" };
    }
}
 

void DataBase::addPhone(const std::string& name, const std::string& phone)
{
    pqxx::work txn(connection_);
    pqxx::result r = txn.exec_params(
        "SELECT id, surname FROM person WHERE name = $1", name);
    if (!r.empty())
    {
        int person_id = r[0][0].as<int>();
        txn.exec_params(
            "INSERT INTO phone (phone_number, person_id) VALUES ($1, $2)", phone, person_id);
        std::string surname = r[0][1].as<std::string>();
        txn.commit();
        std::cout << "Phone number added for " << person_id << " " << name << " " << surname << std::endl;
    }
    else
    {
        txn.abort();
        throw std::string{"Client not found:" + name};
    }
}


void DataBase::changeClient(const std::string& email, const std::string& newName, const std::string& newSurname, const std::string& newEmail)
{
    pqxx::work txn(connection_);
    pqxx::result r =
    txn.exec_params(
        "SELECT id FROM person WHERE email = $1", email);
    if (!r.empty())
    {
        int person_id = r[0][0].as<int>();
        txn.exec_params(
            R"(UPDATE person SET name = $1, surname = $2, email = $3 WHERE id = $4)", newName, newSurname, newEmail, person_id);
        txn.commit();
        std::cout << "Client updated with id: " << person_id << " " << newName << " " << newSurname << " " << newEmail << std::endl;
    }
    else
    {
        txn.abort();
        throw std::string{"Client not found:" + email};
    }
}

void DataBase::deletePhone(const std::string& email, const std::string& phone)
{
    pqxx::work txn(connection_);
    pqxx::result r = txn.exec_params(
    "SELECT id, name, surname FROM person WHERE email = $1", email);
if (!r.empty())
{
    int person_id = r[0][0].as<int>();
    txn.exec_params(
        "DELETE FROM phone WHERE phone_number = $1 AND person_id = $2", phone, person_id);
    txn.commit();
    std::string name = r[0][1].as<std::string>();
    std::string surname = r[0][2].as<std::string>();
    std::cout << "Phone number deleted for " << person_id << " " << name << " " << surname << std::endl;
}
else
{
    txn.abort();
    throw std::string{"Client not found:" + email};
}
}


void DataBase::deleteClient(const std::string& email)
{
    pqxx::work txn(connection_);
    pqxx::result r = txn.exec_params(
        "SELECT id, name, surname FROM person WHERE email = $1", email);
    if (!r.empty())
    {
        int person_id = r[0][0].as<int>();
        std::string name = r[0][1].as<std::string>();
        std::string surname = r[0][2].as<std::string>();
        txn.exec_params(
            "DELETE FROM phone WHERE person_id = $1", person_id);
        txn.exec_params(
            "DELETE FROM person WHERE id = $1", person_id);
        txn.commit();
        std::cout << "Client deleted: " << person_id << " " << name << " " << surname << std::endl;
    }
    else
    {
        txn.abort();
        throw std::string{"Client not found:" + email};
    }
}


std::vector<Client> DataBase::findClient(const std::string& query)
{
std::vector<Client> result;
pqxx::work txn(connection_);
pqxx::result r = txn.exec_params(
    "SELECT * "
    "FROM person "
    "LEFT JOIN public.phone ON public.person.id = public.phone.person_id "
    "WHERE person.name = $1 OR person.surname = $1 OR person.email = $1 OR "
    "phone.phone_number = $1", query);
txn.commit();
for (auto row : r)
{
    Client client;
    client.name_ = row["name"].as<std::string>();
    client.surname_ = row["surname"].as<std::string>();
    client.email_ = row["email"].as<std::string>();
    result.push_back(client);
}
return result;
}

void DataBase::showTable()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    pqxx::work txn(connection_);
    pqxx::result table = txn.exec("SELECT table_name FROM information_schema.tables WHERE table_schema = 'public'");
    for (auto row : table)
    {
        std::string tableName = row[0].as<std::string>();
        std::string query = "SELECT * FROM " + tableName;
        pqxx::result data = txn.exec(query);
        std::cout << "Table: " << tableName << std::endl;
        for (auto row : data)
        {
            for (auto field : row)
            {
                std::cout << field.c_str() << " ";
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
    txn.commit();
    std::cout << "Table data displayed successfully!" << std::endl;
}
