//
// Copyright (C) 2004-2006 Maciej Sobczak, Stephen Hutton
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef SOCI_EMPTY_H_INCLUDED
#define SOCI_EMPTY_H_INCLUDED

#include "soci-backend.h"


namespace SOCI
{

struct EmptyStatementBackEnd;
struct EmptyStandardIntoTypeBackEnd : details::StandardIntoTypeBackEnd
{
    EmptyStandardIntoTypeBackEnd(EmptyStatementBackEnd &st)
        : statement_(st) {}

    virtual void defineByPos(int &position,
        void *data, details::eExchangeType type);

    virtual void preFetch();
    virtual void postFetch(bool gotData, bool calledFromFetch,
        eIndicator *ind);

    virtual void cleanUp();

    EmptyStatementBackEnd &statement_;
};

struct EmptyVectorIntoTypeBackEnd : details::VectorIntoTypeBackEnd
{
    EmptyVectorIntoTypeBackEnd(EmptyStatementBackEnd &st)
        : statement_(st) {}

    virtual void defineByPos(int &position,
        void *data, details::eExchangeType type);

    virtual void preFetch();
    virtual void postFetch(bool gotData, eIndicator *ind);

    virtual void resize(std::size_t sz);
    virtual std::size_t size();

    virtual void cleanUp();

    EmptyStatementBackEnd &statement_;
};

struct EmptyStandardUseTypeBackEnd : details::StandardUseTypeBackEnd
{
    EmptyStandardUseTypeBackEnd(EmptyStatementBackEnd &st)
        : statement_(st) {}

    virtual void bindByPos(int &position,
        void *data, details::eExchangeType type);
    virtual void bindByName(std::string const &name,
        void *data, details::eExchangeType type);

    virtual void preUse(eIndicator const *ind);
    virtual void postUse(bool gotData, eIndicator *ind);

    virtual void cleanUp();

    EmptyStatementBackEnd &statement_;
};

struct EmptyVectorUseTypeBackEnd : details::VectorUseTypeBackEnd
{
    EmptyVectorUseTypeBackEnd(EmptyStatementBackEnd &st)
        : statement_(st) {}

    virtual void bindByPos(int &position,
        void *data, details::eExchangeType type);
    virtual void bindByName(std::string const &name,
        void *data, details::eExchangeType type);

    virtual void preUse(eIndicator const *ind);

    virtual std::size_t size();

    virtual void cleanUp();

    EmptyStatementBackEnd &statement_;
};

struct EmptySessionBackEnd;
struct EmptyStatementBackEnd : details::StatementBackEnd
{
    EmptyStatementBackEnd(EmptySessionBackEnd &session);

    virtual void alloc();
    virtual void cleanUp();
    virtual void prepare(std::string const &query);

    virtual execFetchResult execute(int number);
    virtual execFetchResult fetch(int number);

    virtual int getNumberOfRows();

    virtual std::string rewriteForProcedureCall(std::string const &query);

    virtual int prepareForDescribe();
    virtual void describeColumn(int colNum, eDataType &dtype,
        std::string &columnName);

    virtual EmptyStandardIntoTypeBackEnd * makeIntoTypeBackEnd();
    virtual EmptyStandardUseTypeBackEnd * makeUseTypeBackEnd();
    virtual EmptyVectorIntoTypeBackEnd * makeVectorIntoTypeBackEnd();
    virtual EmptyVectorUseTypeBackEnd * makeVectorUseTypeBackEnd();

    EmptySessionBackEnd &session_;
};

struct EmptyRowIDBackEnd : details::RowIDBackEnd
{
    EmptyRowIDBackEnd(EmptySessionBackEnd &session);

    ~EmptyRowIDBackEnd();
};

struct EmptyBLOBBackEnd : details::BLOBBackEnd
{
    EmptyBLOBBackEnd(EmptySessionBackEnd &session);

    ~EmptyBLOBBackEnd();

    virtual std::size_t getLen();
    virtual std::size_t read(std::size_t offset, char *buf,
        std::size_t toRead);
    virtual std::size_t write(std::size_t offset, char const *buf,
        std::size_t toWrite);
    virtual std::size_t append(char const *buf, std::size_t toWrite);
    virtual void trim(std::size_t newLen);

    EmptySessionBackEnd &session_;
};

struct EmptySessionBackEnd : details::SessionBackEnd
{
    EmptySessionBackEnd(std::string const &connectString);

    ~EmptySessionBackEnd();

    virtual void begin();
    virtual void commit();
    virtual void rollback();

    void cleanUp();

    virtual EmptyStatementBackEnd * makeStatementBackEnd();
    virtual EmptyRowIDBackEnd * makeRowIDBackEnd();
    virtual EmptyBLOBBackEnd * makeBLOBBackEnd();
};

struct EmptyBackEndFactory : BackEndFactory
{
    virtual EmptySessionBackEnd * makeSession(
        std::string const &connectString) const;
};

extern EmptyBackEndFactory const empty;

} // namespace SOCI

#endif // SOCI_EMPTY_H_INCLUDED