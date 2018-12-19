#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

int main() {
	MYSQL *con;
	con = mysql_init(NULL);
	bool cont = true;
	int choice;
	int ID;
	string query;
	string fName;
	string lName;
	string hDate;
	string title;

	con = mysql_real_connect(con,"cstnt.tstc.edu","cpswanson","1498787","cpswanson",0,NULL,0);

	if (con) {
		cout << "Connected" << endl << endl;
	}
	else {
		cout << "Failed to connect." << endl << endl;
	}

	MYSQL_RES *res;
	MYSQL_ROW row;

	do {
		cont = true;

		query = "Select * From cpswanson.Staff";
		mysql_query(con, query.c_str());
		res = mysql_store_result(con);
		if (res != NULL) {
			int col = 0;
			col = mysql_num_fields(res);

			while (((row = mysql_fetch_row(res)) != NULL)) {
				for (int i = 0; i < col; i++) {
					if (i == 0)
						ID = atoi(row[i]);
					cout << row[i] << "   ";
				}
				cout << endl;
			}
		}

		cout << "-------------------\n";
		cout << "1.Add new record\n2.Update existing record\n3.Delete existing record\n4.Exit\n";
		cin >> choice;
		switch (choice)
		{
		case 1: //Add record
			cout << "First name: ";
			cin >> fName;
			cout << "\nLast name: ";
			cin >> lName;
			cout << "\nHire date (YYYY-MM-DD): ";
			cin >> hDate;
			cout << "\nTitle: ";
			cin.ignore();
			getline(cin, title);
			query = "Insert Into cpswanson.Staff(StaffID,FirstName,LastName,HireDate,Title)Values("
				+ to_string(ID + 1) + ",'" + fName + "','" + lName + "','" + hDate + "','" + title + "')";
			mysql_query(con, query.c_str());
			
			break;
		case 2:	//Update record
			cout << "Enter the ID of the employee you wish to update: ";
			cin >> ID;
			cout << "\nFirst name: ";
			cin >> fName;
			cout << "\nLast name: ";
			cin >> lName;
			cout << "\nHire date(YYYY-MM-DD): ";
			cin >> hDate;
			cout << "\nTitle: ";
			cin.ignore();
			getline(cin, title);
			query = "Update cpswanson.Staff Set FirstName = '" + fName
				+ "',LastName = '" + lName + "',HireDate = '" + hDate
				+"',Title = '" + title + "' Where StaffID = " + to_string(ID);
			mysql_query(con, query.c_str());

			break;
		case 3:	//Delete record
			cout << "Enter the ID of the employee you wish to delete: ";
			cin >> ID;
			query = "Delete From cpswanson.Staff Where StaffID = " + to_string(ID);
			mysql_query(con, query.c_str());
			
			break;
		case 4:
			cont = false;
			break;
		default:
			break;
		}
	} while (cont == true);

	mysql_close(con);

	return 0;
}