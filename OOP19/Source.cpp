#include <iostream>
#include <vector>

using namespace std;

class NotFoundException : public exception {
	string message;
public:
	NotFoundException(string message) : message(message) {}

	const char* what() const override {
		return message.c_str();
	}

};

class NotEmptyPlace : public exception {
	string message;
public:
	NotEmptyPlace(string message) : message(message) {}

	const char* what() const override {
		return message.c_str();
	}

};




class Disc {
protected:
	double current_size = 0;
	class File {
	private:
		double file_size;
	public:
		string filename;
		string content;
		double getfile_size() {
			return file_size;
		}
		File(string filename, string content = "") {
			this->filename = filename;
			this->content = content;
			file_size = content.size();
		}
	};

	vector<File*> files;

public:
	const static double max_size;

	bool isExistsFile(string filename) {
		for (File* file : files) {
			if (file->filename == filename)
				return true;
		}
		return false;
	}

	virtual File& getFile(string filename) = 0;

	virtual void createFile(string filename, string content = "") = 0;

	virtual void setFileContent(string filename, string content = "") = 0;

	virtual void deleteFileContent(string filename, string content = "") = 0;
};
const double Disc::max_size = 1024;

class HDD : public Disc {

public:

	File& getFile(string filename) override {
		for (File* file : files) {
			if (file->filename == filename)
				return *file;
		}
		throw NotFoundException("file tapilmadi");
	}

	void createFile(string filename, string content = "") override {
		if (isExistsFile(filename)) {
			throw "eyni adli file yaratmaq olmaz";
		}
		File* newFile = new File(filename, content);
		if (max_size < current_size + newFile->getfile_size())
			throw NotEmptyPlace("bosh yer yoxdur");
		files.push_back(newFile);
		current_size += newFile->getfile_size();
	}

	void setFileContent(string filename, string content = "") override {
		if (isExistsFile(filename)) {

			File& file = getFile(filename);
			current_size -= file.getfile_size();
			if (current_size + content.size() < max_size) {
				file.content = content;
				current_size += content.size();
				return;
			}
			throw  "Yer yoxdu";

		}
		throw NotFoundException("Fayl tapilmadi");

	}

	void deleteFileContent(string filename, string content = "") override {
		if (isExistsFile(filename))
		{
			File& file = getFile(filename);
			current_size -= file.getfile_size();
			if (current_size + content.size() < max_size)
			{
				file.content = " ";
				current_size += content.size();
				return;
			}
			throw "Yer yoxdu ";
		}
		throw  NotFoundException("Fayl tapilmadi");
	}
};

class SSD : public Disc {
public:
	virtual File& getFile(string filename) override
	{
		{
			for (File* file : files) {
				if (file->filename == filename)
					return *file;
			}
			throw NotFoundException("file tapilmadi");
		}
	}

	virtual void createFile(string filename, string content = "") override
	{
		if (isExistsFile(filename)) {
			throw "eyni adli file yaratmaq olmaz";
		}
		File* newFile = new File(filename, content);
		if (max_size < current_size + newFile->getfile_size())
			throw NotEmptyPlace("bosh yer yoxdur");
		files.push_back(newFile);
		current_size += newFile->getfile_size();
	}
	virtual void setFileContent(string filename, string content = "") override
	{
		if (isExistsFile(filename)) {

			File& file = getFile(filename);
			current_size -= file.getfile_size();
			if (current_size + content.size() < max_size) {
				file.content = content;
				current_size += content.size();
				return;
			}
			throw  "Yer yoxdu";

		}
		throw NotFoundException("Fayl tapilmadi");
	}
	virtual void deleteFileContent(string filename, string content = "") override
	{
		if (isExistsFile(filename)) {

			File& file = getFile(filename);
			current_size -= file.getfile_size();
			if (current_size + content.size() < max_size) {
				file.content = " ";
				current_size += content.size();
				return;
			}
			throw  "Yer yoxdu";

		}
		throw NotFoundException("Fayl tapilmadi");
	}
};


class OperationSystem {
	OperationSystem() {}
public:
	static void controlPC();
};

void OperationSystem::controlPC() {
	HDD hd;
	try {
		hd.createFile("newtext.txt", "hello world");

		hd.getFile("newtext.txt");
	}
	catch (const exception& ex) {
		cout << "Error : " << ex.what() << endl;
	}
}

void main() {
	OperationSystem::controlPC();

}