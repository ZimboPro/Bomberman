#ifndef ERRORREFACTOR_HPP
#define ERRORREFACTOR_HPP

#include <stdexcept>
#include <string>

class Error {
    public:
        class InitError: public std::exception
        {
            public:
                InitError(std::string const & str);
                InitError();
                ~InitError();
                InitError(InitError const & rhs);
                InitError & operator=(InitError const & rhs);
                virtual const char* what() const throw();
            private:
                std::string e_msg;
        };
        class CreateWindowError: public std::exception
        {
            public:
                CreateWindowError(std::string const & str);
                CreateWindowError();
                ~CreateWindowError();
                CreateWindowError(CreateWindowError const & rhs);
                CreateWindowError & operator=(CreateWindowError const & rhs);
                virtual const char* what() const throw();
            private:
                std::string e_msg;
        };
        class WindowMaxSizeError: public std::exception
        {
            public:
                WindowMaxSizeError(std::string const & str);
                WindowMaxSizeError();
                ~WindowMaxSizeError();
                WindowMaxSizeError(WindowMaxSizeError const & rhs);
                WindowMaxSizeError & operator=(WindowMaxSizeError const & rhs);
                virtual const char* what() const throw();
            private:
                std::string e_msg;
        };
        class WindowMinSizeError: public std::exception
        {
            public:
                WindowMinSizeError(std::string const & str);
                WindowMinSizeError();
                ~WindowMinSizeError();
                WindowMinSizeError(WindowMinSizeError const & rhs);
                WindowMinSizeError & operator=(WindowMinSizeError const & rhs);
                virtual const char* what() const throw();
            private:
                std::string e_msg;
        };
        class NoDLOpen: public std::exception
        {
            public:
                NoDLOpen(std::string const & str);
                NoDLOpen();
                ~NoDLOpen();
                NoDLOpen(NoDLOpen const & rhs);
                NoDLOpen & operator=(NoDLOpen const & rhs);
                virtual const char* what() const throw();
            private:
                std::string e_msg;
        };
        class DLError: public std::exception
        {
            public:
                DLError(std::string const & str);
                DLError();
                ~DLError();
                DLError(DLError const & rhs);
                DLError & operator=(DLError const & rhs);
                virtual const char* what() const throw();
            private:
                std::string e_msg;
        };
};

#endif
