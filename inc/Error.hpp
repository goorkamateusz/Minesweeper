/**
 * \file Error.hpp
 * \author Górka Mateusz
 * \brief Error handling classes
 *
 * @copyright Copyright (c) 2020
 *
 */

/**
 * \brief Error virtual class
 *
 */
class Error {
public:
    virtual const char* what() const { return "Unnamed error!"; }
};


////-----------------------------------------------------------

/**
 * \brief Class of Alloc errors
 *
 */
class ErrAlloc : public Error {
public:
    const char* what() const { return "Allocation error!"; }
};


/**
 * \brief Error Input
 */
class ErrInput : public Error {
private:
    const char* info;

public:
    inline ErrInput( const char* txt ): info(txt){}
    const char* what() const { return info; }
};

/**
 * \brief Error
 */
class ErrSys : public Error {
private:
    const char* info;

public:
    inline ErrSys( const char* txt ): info(txt){}
    const char* what() const { return info; }
};


/**
 * \brief End game exception.
 */
class EndGame : public Error {
private:
    const char* info;

public:
    inline EndGame( const char* txt ): info(txt){}
    const char* what() const { return info; }
};