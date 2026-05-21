//
//  Query.hpp
//  mailcore2
//
//  Created by Ben Gotow on 6/20/17.
//  Copyright © 2017 MailCore. All rights reserved.
//

#ifndef Query_hpp
#define Query_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include <SQLiteCpp/SQLiteCpp.h>

#include "json.hpp"

using namespace nlohmann;
using namespace std;


class Query {
    json _clauses;
    int _limit;
    string _orderBy;
    string _orderDir;

public:
    Query() noexcept;

    Query & equal(const string& col, const string& val);
    Query & equal(const string& col, double val);
    Query & equal(const string& col, const vector<string> & val);
    Query & equal(const string& col, const vector<uint32_t> & val);

    Query & gt(const string& col, double val);
    Query & gte(const string& col, double val);
    Query & lt(const string& col, double val);
    Query & lte(const string& col, double val);

    Query & limit(int l);
    Query & orderBy(const string& col, const string& dir = "ASC");

    int getLimit();
    std::string getSQL();

    void bind(SQLite::Statement & query);
};


#endif /* Query_hpp */
