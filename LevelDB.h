#include <iostream>
#include <sstream>

#include "leveldb/db.h"
#include "snappy.h"

#ifndef LEVELDB_PLAYGROUND_LEVELDB_H
#define LEVELDB_PLAYGROUND_LEVELDB_H

using namespace std;

class LevelDB {

private:
	leveldb::DB *db;
	leveldb::WriteOptions write_options;
	int INVALID = -1;

public:
	LevelDB();
	~LevelDB();

	int init_db(const string);
	void close_db();

	void set_data(string, string);
	void delete_data(string);
	void display_data();

	string compress_data(string);
	string decompress_data(string);

	void delete_all();

};


#endif //LEVELDB_PLAYGROUND_LEVELDB_H
