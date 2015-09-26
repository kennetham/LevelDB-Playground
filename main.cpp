#include <iostream>
#include <sstream>

#include "leveldb/db.h"
#include "snappy.h"

using namespace std;

int main(int argc, char **argv) {
	// Set up database connection information and open database
	leveldb::DB *db;
	leveldb::Options options;
	options.create_if_missing = true;

	leveldb::Status status = leveldb::DB::Open(options, "./leveldb_test", &db);

	if (!status.ok()) {
		cerr << "Unable to open/create database './leveldb_test'" << endl;
		cerr << status.ToString() << endl;
		return -1;
	}

	string compressed_info;
	string uncompressed_info = "The quick brown fox jumps over the lazy dog";
	string output;

	snappy::Compress(uncompressed_info.data(), uncompressed_info.size(), &output);
	cout << &output << "\n";

	snappy::Uncompress(output.data(), output.size(), &compressed_info);
	cout << &compressed_info << "\n";

	// Add sample values into Database
	leveldb::WriteOptions write_options;

	ostringstream key;
	key << "Test Key";

	ostringstream value;
	value << "Test Value";

	db->Put(write_options, key.str(), value.str());

	ostringstream key_name;
	key_name << "Kenneth Ham";

	ostringstream value_details;
	value_details << "Entrepreneur, Software Engineer";

	db->Put(write_options, key_name.str(), value_details.str());

	ostringstream redundant_key;
	redundant_key << &output;

	ostringstream redundant_value;
	redundant_value << compressed_info;

	db->Put(write_options, redundant_key.str(), redundant_value.str());

	// Iterate over each item in the database and print them
	leveldb::Iterator *kv_iterator = db->NewIterator(leveldb::ReadOptions());

	for (kv_iterator->SeekToFirst(); kv_iterator->Valid(); kv_iterator->Next()) {
		cout << kv_iterator->key().ToString() << " : " << kv_iterator->value().ToString() << endl;
	}

	// Deletes a key value from database
	db->Delete(write_options, redundant_key.str());
	cout << "Deletes a key & value from DB\n";

	// Updates iterator to get new DB values
	kv_iterator = db->NewIterator(leveldb::ReadOptions());

	for (kv_iterator->SeekToFirst(); kv_iterator->Valid(); kv_iterator->Next()) {
		cout << kv_iterator->key().ToString() << " : " << kv_iterator->value().ToString() << endl;
	}

	if (!kv_iterator->status().ok()) {
		cerr << "An error was found during the scan" << endl;
		cerr << kv_iterator->status().ToString() << endl;
	}

	delete kv_iterator;

	// Close the database
	delete db;
}
