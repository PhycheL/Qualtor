#pragma once
#include <string>
#include <vector>
#include <list>
#include <boost/any.hpp>
using namespace std;
typedef std::list<boost::any> list_any;
vector<int> filter_integers(list_any values);
boost::any compare_one(boost::any a,boost::any b);
