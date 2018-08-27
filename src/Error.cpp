#include "Error.hpp"


Error::AssetError::AssetError(std::string const & str) { e_msg = str; }

Error::AssetError::AssetError() { e_msg = "Asset Error"; }

Error::AssetError::~AssetError() {}

Error::AssetError::AssetError(AssetError const & rhs) { this->e_msg = rhs.e_msg; }

Error::AssetError & Error::AssetError::AssetError::operator=(AssetError const & rhs) {
	this->e_msg = rhs.e_msg;
	return *this;
}

const char* Error::AssetError::what() const throw() { return e_msg.c_str(); }



Error::InitError::InitError(std::string const & str) { e_msg = str; }

Error::InitError::InitError() { e_msg = "Error Initialising library"; }

Error::InitError::~InitError() {}

Error::InitError::InitError(InitError const & rhs) { this->e_msg = rhs.e_msg; }

Error::InitError & Error::InitError::operator=(InitError const & rhs) { 
	this->e_msg = rhs.e_msg; 
	return *this; 
}

const char* Error::InitError::what() const throw() { return e_msg.c_str(); }



Error::CreateWindowError::CreateWindowError(std::string const & str) { e_msg = str; }

Error::CreateWindowError::CreateWindowError() { e_msg = "Error creating window"; }

Error::CreateWindowError::~CreateWindowError() {}

Error::CreateWindowError::CreateWindowError(CreateWindowError const & rhs) { this->e_msg = rhs.e_msg; }

Error::CreateWindowError & Error::CreateWindowError::CreateWindowError::operator=(CreateWindowError const & rhs) { 
	this->e_msg = rhs.e_msg; 
	return *this; 
}

const char* Error::CreateWindowError::what() const throw() { return e_msg.c_str(); }



Error::WindowMaxSizeError::WindowMaxSizeError(std::string const & str) { e_msg = str; }

Error::WindowMaxSizeError::WindowMaxSizeError() { e_msg = "Parameters exceeds max allowed values"; }

Error::WindowMaxSizeError::~WindowMaxSizeError() {}

Error::WindowMaxSizeError::WindowMaxSizeError(WindowMaxSizeError const & rhs) { this->e_msg = rhs.e_msg; }

Error::WindowMaxSizeError & Error::WindowMaxSizeError::WindowMaxSizeError::operator=(WindowMaxSizeError const & rhs) { 
	this->e_msg = rhs.e_msg; 
	return *this;
}

const char* Error::WindowMaxSizeError::WindowMaxSizeError::what() const throw() { return e_msg.c_str(); }



Error::WindowMinSizeError::WindowMinSizeError(std::string const & str) { e_msg = str; }

Error::WindowMinSizeError::WindowMinSizeError() { e_msg = "Parameters is less than min allowed values"; }

Error::WindowMinSizeError::~WindowMinSizeError() {}

Error::WindowMinSizeError::WindowMinSizeError(WindowMinSizeError const & rhs) { this->e_msg = rhs.e_msg; }

Error::WindowMinSizeError & Error::WindowMinSizeError::WindowMinSizeError::operator=(WindowMinSizeError const & rhs) { 
	this->e_msg = rhs.e_msg; 
	return *this; 
}

const char* Error::WindowMinSizeError::WindowMinSizeError::what() const throw() { return e_msg.c_str(); }



Error::NoDLOpen::NoDLOpen(std::string const & str) { e_msg = str; }

Error::NoDLOpen::NoDLOpen() { e_msg = "No Dynamic Library Open Error"; }

Error::NoDLOpen::~NoDLOpen() {}

Error::NoDLOpen::NoDLOpen(NoDLOpen const & rhs) { this->e_msg = rhs.e_msg; }

Error::NoDLOpen & Error::NoDLOpen::NoDLOpen::operator=(NoDLOpen const & rhs) { 
	this->e_msg = rhs.e_msg; 
	return *this; 
}

const char* Error::NoDLOpen::what() const throw() { return e_msg.c_str(); }



Error::DLError::DLError(std::string const & str) { e_msg = str; }

Error::DLError::DLError() { e_msg = "Dynamic Library Error"; }

Error::DLError::~DLError() {}

Error::DLError::DLError(DLError const & rhs) { this->e_msg = rhs.e_msg; }

Error::DLError & Error::DLError::DLError::operator=(DLError const & rhs) { 
	this->e_msg = rhs.e_msg; 
	return *this; 
}

const char* Error::DLError::what() const throw() { return e_msg.c_str(); }
