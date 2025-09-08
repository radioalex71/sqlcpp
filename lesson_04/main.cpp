#include "Task_01.h"



int main()
{
    try
    {
        std::string connectString = 
            "host=localhost "
            "port=5432 "
            "dbname=postgres "
            "user=postgres "
            "password=Data_Base25 ";
       
        DataBase db(connectString);
        
        db.dropTable();
        
        try
        {
            db.createTable();
            db.showTable();
        }
        catch (std::string error_masage)
        {
            std::cout << error_masage << std::endl;
        }

        try
        {
            db.addClient("Ivan", "Ivanov", "ivanov@mail.ru", "89999999999");
            db.showTable();
        }
        catch (std::string error_masage)
        {
            std::cout << error_masage << std::endl;
        }

        try
        {
            db.addClient("Petr", "Petrov", "petrov@mail.ru", "88888888888");
            db.showTable();
        }
        catch (std::string error_masage)
        {
        std::cout << error_masage << std::endl;
        }
        

        try
        {
            db.addPhone("Ivan", "87777777777");
            db.showTable();
        }
        catch (std::string error_masage)
        {
            std::cout << error_masage << std::endl;
        }

        try
        {
            db.addPhone("Petr", "86666666666");
            db.showTable();
        }
        catch (std::string error_masage)
        {
            std::cout << error_masage << std::endl;
        }

        try
        {
            db.changeClient("ivanov@mail.ru", "Ivann", "Ivanovv", "ivanovv@mail.ru");
            db.showTable();
        }
        catch (std::string error_masage)
        {
            std::cout << error_masage << std::endl;
        }

        try
        {
            db.deletePhone("ivanovv@mail.ru", "89999999999");
            db.showTable();
        }
        catch (std::string error_masage)
        {
            std::cout << error_masage << std::endl;
        }

        try
        {
            db.deleteClient("ivanovv@mail.ru");
            db.showTable();
        }
        catch (std::string error_masage)
        {
            std::cout << error_masage << std::endl;
        }

        std::vector<Client> clients = db.findClient("Petr");
        for (const auto& client : clients)
        {
            std::cout << "Found client: " << client.name_ << ", Surname: " << client.surname_ << ", Email: " << client.email_ << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
        std::cout << "Error connect: " << e.what() << std::endl;
    }

    return 0;
}
