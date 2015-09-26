#include "LevelDB.h"

using namespace std;

int main() {
	LevelDB *ldb = new LevelDB();

	ldb->init_db("leveldb_test");
	ldb->delete_all();

	ldb->set_data("key", "value");
	ldb->set_data("Kenneth Ham", "Entrepreneur, Software Engineer");
	ldb->set_data("Languages", "C++, Ruby, Java, C#, Scala, Python");
	ldb->set_data("Companies", "Microsoft, Google, Facebook");
	ldb->display_data();

	cout << "\n";

	ldb->delete_data("key");
	ldb->display_data();
	cout << "\n";

	cout << ldb->get_data("Kenneth Ham");

	ldb->delete_all();
	ldb->close_db();
}
