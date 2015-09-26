#include "LevelDB.h"

LevelDB::LevelDB() { }

LevelDB::~LevelDB() {
	delete db;
}

int LevelDB::init_db(const string db_name) {
	// Set up database connection information and open database
	leveldb::Options options;
	options.create_if_missing = true;

	leveldb::Status status = leveldb::DB::Open(options, "./" + db_name, &db);

	if (!status.ok()) {
		cerr << "Unable to open/create database" << endl;
		cerr << status.ToString() << endl;

		return INVALID;
	}

	return 1;
}

void LevelDB::close_db() {
	delete db;
}

void LevelDB::set_data(string key, string value) {
	ostringstream key_stream;
	key_stream << key;

	ostringstream value_stream;
	value_stream << value;

	db->Put(write_options, key_stream.str(), value_stream.str());
}

void LevelDB::delete_data(string key) {
	db->Delete(write_options, key);
}

void LevelDB::display_data() {
	leveldb::Iterator *kv_iterator = db->NewIterator(leveldb::ReadOptions());

	for (kv_iterator->SeekToLast(); kv_iterator->Valid(); kv_iterator->Prev()) {
		cout << kv_iterator->key().ToString() << " : " << kv_iterator->value().ToString() << endl;
	}

	if (!kv_iterator->status().ok()) {
		cerr << "An error was found during the scan" << endl;
		cerr << kv_iterator->status().ToString() << endl;
	}

	delete kv_iterator;
}

string LevelDB::compress_data(string uncompress_data) {
	string output;
	snappy::Compress(uncompress_data.data(), uncompress_data.size(), &output);

	return output;
}

string LevelDB::decompress_data(string compress_data) {
	string output;
	snappy::Uncompress(compress_data.data(), compress_data.size(), &output);

	return output;
}

void LevelDB::delete_all() {
	leveldb::Iterator *kv_iterator = db->NewIterator(leveldb::ReadOptions());

	for (kv_iterator->SeekToLast(); kv_iterator->Valid(); kv_iterator->Prev()) {
		db->Delete(write_options, kv_iterator->key().ToString());
	}

	if (!kv_iterator->status().ok()) {
		cerr << "An error was found during the scan" << endl;
		cerr << kv_iterator->status().ToString() << endl;
	}

	delete kv_iterator;
}