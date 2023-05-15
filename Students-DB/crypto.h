#pragma once

void Encrypt(string path) {
	system(("OpenSSL-Win64\\bin\\openssl.exe enc -aes-256-cbc -salt -in " + path + " -out " + path + ".enc -k " + userPasswd + " >nul 2>&1").c_str());
	system(CLEAR_COMMAND);
}

void Decrypt(string path) {
	system(("OpenSSL-Win64\\bin\\openssl.exe enc -d -aes-256-cbc -in " + path + ".enc -out " + path + " -k " + userPasswd + " >nul 2>&1").c_str());
	system(CLEAR_COMMAND);
}

string GetEncPasswd() {
	char passwd[100]{};
	system("OpenSSL-Win64\\bin\\openssl.exe rsautl -decrypt -inkey .openssl-keys\\id_rsa -in .openssl-keys\\passwd.enc -out .openssl-keys\\passwd");

	ifstream ifs;
	ifs.open(".openssl-keys\\passwd", ios::in);
	ifs >> passwd;
	ifs.close();

	DeleteFileByFilename(".openssl-keys\\passwd");

	return passwd;
}
