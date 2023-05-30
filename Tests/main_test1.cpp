/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test1.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:21:32 by I-lan             #+#    #+#             */
/*   Updated: 2023/02/01 13:49:33 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <map>
#include <ctime>
#include <stack>

#include "../Includes/Containers/map.hpp"
#include "../Includes/Containers/stack.hpp"
#include "../Includes/Containers/vector.hpp"

#include "../Includes/Utils/algorithm.hpp"
#include "../Includes/Utils/binary_search_tree.hpp"
#include "../Includes/Utils/iterator.hpp"
#include "../Includes/Utils/type_traits.hpp"
#include "../Includes/Utils/utility.hpp"

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

using std::cout;

template <class Key, class T>
static std::ostream& operator<<(std::ostream& o, const NAMESPACE::pair<Key, T>& p)
{
	return o << "(" << p.first << ", " << p.second << ")";
}

std::string get_namespace()
{
#define ft 0
#define std 1

#if NAMESPACE==ft
	return "ft";
#elif NAMESPACE==std
	return "std";
#else
	return "unkown";
#endif

#undef ft
#undef std
}

void display_namespace()
{
	cout << "### used namespace: " + get_namespace() + " ###\n";
}

void reverse_iterator_tests()
{
	using NAMESPACE::reverse_iterator;
	cout << "--- reverse iterator tests: ---\n";
	std::vector<int> v(5, 6);
	reverse_iterator<std::vector<int>::iterator> rit(v.end());
	while (rit != static_cast<reverse_iterator<std::vector<int>::iterator> >(v.begin()))
		cout << *rit++;
	std::cout << '\n';
	cout << (rit > rit + 1);
	cout << (rit < rit - 2);
	cout << (rit >= rit - 2);
	cout << (rit <= rit + 1);
	cout << *(--rit - 2) << '\n';
	reverse_iterator<std::vector<int>::iterator> rit2(v.begin());
	cout << (rit2 == rit);
	rit = rit2;
	cout << (rit2 == rit);
	cout << *(rit2 -= 3);
	cout << *(rit2 += 2) << '\n';
	rit2 = static_cast<reverse_iterator<std::vector<int>::iterator> >(v.end());
	for (int i = 0; i < 4; i++)
		std::cout << rit2[i];
	std::cout << '\n';
	std::map<int, std::string> m;
	m[0] = "ko";
	m[1] = "je pense";
	m[2] = "donc";
	m[3] = "je suis";
	reverse_iterator<std::map<int, std::string>::iterator> rit3(m.end());
	while (rit3 != static_cast<reverse_iterator<std::map<int, std::string>::iterator> >(m.begin()))
	{
		std::cout << "first: " << rit3->first << "second: " << rit3->second << '\n';
		rit3++;
	}
}

void is_integral_tests()
{
	using ft::is_integral; //cannot use std (needs at least c++11)
	cout << "--- is_integral tests: ---\n";
	cout << "int: " << is_integral<int>::value << '\n';
	cout << "float: " << is_integral<float>::value << '\n';
	cout << "unsigned long: " << is_integral<unsigned long>::value << '\n';
	cout << "const volatile char: " << is_integral<const volatile char>::value << '\n';
	cout << "const volatile unsigned long long: " << is_integral<const volatile unsigned long long>::value << '\n';
	cout << "std::string: " << is_integral<std::string>::value << '\n';
	cout << "const short: " << is_integral<const short>::value << '\n';
	cout << "volatile short: " << is_integral<volatile short>::value << '\n';
	cout << "volatile double: " << is_integral<volatile double>::value << '\n';
}

bool mycompare1(float a, float b) { return a == b; }
bool mycompare2(float a, float b) { return a < b;  }
void equal_tests()
{
	cout << "--- equal tests: ---\n";
	std::vector<float> v(3, -0.42f);
	v[0] = 5;
	v[1] = -8;
	std::list<float> m(v.begin(), v.end());
	cout << NAMESPACE::equal(v.begin(), v.end(), m.begin());
	cout << NAMESPACE::equal(v.begin(), v.end(), m.begin(), mycompare1);
	cout << NAMESPACE::equal(v.begin(), v.end(), m.begin(), mycompare2);
	m.front() = 0;
	cout << NAMESPACE::equal(v.begin(), v.end(), m.begin());
	cout << NAMESPACE::equal(v.begin(), v.end(), m.begin(), mycompare1);
	cout << NAMESPACE::equal(v.begin(), v.end(), m.begin(), mycompare2);
	cout << '\n';
}

void lexicographical_tests()
{
	cout << "--- lexicographical_compare tests: ---\n";
	std::string s1 = "je suis pretty";
	std::string s2 = "je suis ugly;";
	cout << NAMESPACE::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
	cout << NAMESPACE::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), mycompare1);
	cout << NAMESPACE::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), mycompare2);
	s1 = "";
	cout << NAMESPACE::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
	cout << NAMESPACE::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), mycompare1);
	cout << NAMESPACE::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), mycompare2);
	s2 = "";
	cout << NAMESPACE::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
	cout << NAMESPACE::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), mycompare1);
	cout << NAMESPACE::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), mycompare2);
	cout << '\n';
}

template <class T1, class T2>
void pair_display(const NAMESPACE::pair<T1, T2>& p)
{
	cout << p.first << ' ' << p.second << '\n';
}

void pair_tests()
{
	cout << "--- pair/make_pair tests: ---\n";
	using NAMESPACE::pair;
	using NAMESPACE::make_pair;
	pair<int, float> p1 = make_pair(5, 10);
	pair_display(p1);
	p1 = make_pair(5.5, 10.5);
	pair_display(p1);
	pair_display(make_pair("coucou", 0x42));
	pair_display(make_pair("coucou", (void*)0));
	pair<int, float> p2 = p1;
	p2.first += 5;
	p2.second -= 5;
	pair_display(p2);
}

template <class InputIt>
void display_range(InputIt first, InputIt last)
{
	while (first != last)
	{
		cout << *first << ' ';
		first++;
	}
	cout << '\n';
}

void vector_tests()
{
	cout << "--- " + get_namespace() + "::vector tests ---\n";
	using NAMESPACE::vector;
	using NAMESPACE::swap;
	vector<int> v1(5, 8);
	v1.push_back(-7);
	display_range(v1.begin(), v1.end());
	cout << v1.empty() << '\n';
	v1.clear();
	cout << v1.empty() << '\n';
	v1.push_back(4242);
	v1.push_back(42);
	v1.push_back(-4242);
	v1.push_back(4242 - 10);
	display_range(v1.begin(), v1.end());
	v1.pop_back();
	v1.pop_back();
	display_range(v1.begin(), v1.end());
	vector<int> v2(5, 8);
	v2 = v1;
	v1.push_back(85);
	vector<int> v3(v1);
	vector<int> v4(v2.get_allocator());
	v3.insert(v3.begin() + 1, v2.begin(), v2.end());
	v4.insert(v4.end(), v1.begin(), v1.end());
	v1.push_back(-999);
	v2.push_back(-995);
	display_range(v1.begin(), v1.end());
	display_range(v2.begin(), v2.end());
	display_range(v3.begin(), v3.end());
	display_range(v4.begin(), v4.end());
	v1.insert(v1.begin(), 5, 8);
	v1.insert(v1.begin() + 2, 6, -7);
	display_range(v1.begin(), v1.end());
	display_range(v2.begin(), v2.end());
	display_range(v3.begin(), v3.end());
	display_range(v4.begin(), v4.end());
	cout << v1.front() << v1.back() << '\n';
	v1.front() = 5;
	v1.back() = 6;
	for (std::size_t i = 0; i < v1.size(); i++)
	{
		cout << v1.at(i);
		cout << v1[i];
	}
	cout << "\n";
	v1.assign(20, 80);
	cout << "capacity after first assign: " << v1.capacity() << '\n';
	display_range(v1.begin(), v1.end());
	v1.assign(11, 3);
	cout << "capacity after second assign: " << v1.capacity() << '\n';
	display_range(v1.begin(), v1.end());
	cout << "gonna assign v2 to v1 \nv1: ";
	display_range(v1.begin(), v1.end());
	cout << "v2: ";
	display_range(v2.begin(), v2.end());
	v1.assign(v2.begin(), v2.end());
	display_range(v1.begin(), v1.end());
	swap(v1, v2);
	display_range(v1.begin(), v1.end());
	swap(v1, v2);
	display_range(v1.begin(), v1.end());
	for (vector<int>::reverse_iterator it = v1.rbegin(); it != v1.rend(); it++)
		cout << *it;
	const vector<int> cv1 = v1;
	for (vector<int>::const_reverse_iterator it = cv1.rbegin(); it != cv1.rend(); it++)
		cout << *it;
	display_range(cv1.begin(), cv1.end());
	cout << '\n';
	cout << v1.empty() << '\n';;
	v1.clear();
	cout << v1.empty() << '\n';;
	v1 = cv1;
	cout << "max size: " << v1.max_size() << '\n';
	cout << "v1 capacity: " << v1.capacity() << '\n';
	cout << "cv1 capacity: " << cv1.capacity() << '\n';
	v1.reserve(2);
	cout << "v1 capacity: " << v1.capacity() << '\n';
	v1.reserve(200);
	cout << "v1 capacity: " << v1.capacity() << '\n';
	display_range(v1.begin(), v1.end());
	v1.resize(175, 8);
	v1.resize(45, 42);
	display_range(v1.begin(), v1.end());
	v1.erase(v1.begin());
	v1.erase(v1.begin() + 2);
	display_range(v1.begin(), v1.end());
	vector<float> empty;
	for (int i = 1; i < 10; i++)
	{
		empty.push_back(42);
		cout << "capacity after " << i << " push_backs: " << empty.capacity() << '\n';
	}
	empty.clear();
	cout << "capacity after calling clear(): " << empty.capacity() << '\n';
	empty = vector<float>();
	cout << "capacity after calling empty assignment: " << empty.capacity() << '\n';
	vector<float> empty2;
	empty2.insert(empty2.begin(), 5, 42);
	cout << "capacity after insert of 5 elems: " << empty2.capacity() << '\n';
	empty2.insert(empty2.begin() + 2, 8, 43);
	cout << "capacity after insert of 8 more elems: " << empty2.capacity() << '\n';
	empty2.insert(empty2.begin() + 2, 1, 44);
	cout << "capacity after insert of 1 more elems: " << empty2.capacity() << '\n';
}

static double operator-(const timespec& a, const timespec& b)
{
	return (a.tv_sec + a.tv_nsec / 1000000000.) - (b.tv_sec + b.tv_nsec / 1000000000.);
}

static void vector_benchmark()
{
	using NAMESPACE::vector;
	timespec tp1, tp2;
	cout << "--- " + get_namespace() + "::vector benchmark ---\n";
	vector<int> pv;
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 420; i++)
		pv.push_back(i);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "420 push_backs: " << tp2 - tp1 << "s\n";
	pv.clear();
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 4200; i++)
		pv.push_back(i);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "4200 push_backs: " << tp2 - tp1 << "s\n";
	pv.clear();
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 42000; i++)
		pv.push_back(i);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "42000 push_backs: " << tp2 - tp1 << "s\n";
	pv.clear();
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 420000; i++)
		pv.push_back(i);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "420000 push_backs: " << tp2 - tp1 << "s\n";
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 50; i++)
		vector<int> tmp(pv);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "50 big copy constructions: " << tp2 - tp1 << "s\n";
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 10; i++)
		pv.assign(5000, 42);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "10 big assigns: " << tp2 - tp1 << "s\n";
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 100; i++)
		pv.assign(5, 42);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "100 small assigns: " << tp2 - tp1 << "s\n";
	vector<int> tmp(5000, 42);
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 10; i++)
		pv.assign(tmp.begin(), tmp.end());
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "10 big assigns iterators: " << tp2 - tp1 << "s\n";
	tmp = vector<int>(5, 42);
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 100; i++)
		pv.assign(tmp.begin(), tmp.end());
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "100 small assigns iterators: " << tp2 - tp1 << "s\n";
	vector<int> rv(500, 42);
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 1; i < 5000; i++)
		rv.reserve(i);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "reserve 1 -> 5000: " << tp2 - tp1 << "s\n";
	tmp = vector<int>(5, 10);
	pv = vector<int>(5, 10);
	tmp.insert(tmp.end(), 90000, 43);
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 2000; i++)
		tmp.insert(tmp.begin() + 2, 5, 42);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "2000 * 5 insert: " << tp2 - tp1 << "s\n";
	tmp.insert(tmp.end(), 90000, 43);
	while (tmp.empty())
		tmp.pop_back();
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "big pop_back: " << tp2 - tp1  << "s\n";
	vector<int> ok;
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 42000; i++)
		ok.resize(i, 42);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "increasing resize: " << (tp2 - tp1) << "s\n";
		clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 42000; i >= 0; i--)
		ok.resize(i, 43);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "decreasing resize: " << (tp2 - tp1)  << "s\n";	
	tmp.insert(tmp.end(), 90000, 43);
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	while (tmp.empty())
		tmp.erase(tmp.begin());
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "big single erase: " << (tp2 - tp1) * 100 << "s\n";
	tmp.insert(tmp.end(), 900000, 43);
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	while (tmp.empty())
		tmp.erase(tmp.begin(), tmp.begin() + 5);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "big range erase: " << (tp2 - tp1) * 100 << "s\n";
	
}

static void stack_tests()
{
	cout << "--- " + get_namespace() + "::stack tests ---\n";
	using NAMESPACE::stack;
	using NAMESPACE::vector;
	stack<int, vector<int> > s1, s2, s3;
	for (int i = 0; i <  20; i++)
		s1.push(i);
	for (int i = 0; i <  21; i++)
		s2.push(i);
	cout << s1.empty() << s3.empty() << '\n';
	cout << s1.size() << s3.size() << '\n';
	cout << s1.top() << s2.top() << '\n';
	stack<int, vector<int> > s4(s1);
	s4 = s2;
	while (!s4.empty())
	{
		cout << s4.top() << '\n';
		s4.pop();
	}
}

void stack_benchmark()
{
	using NAMESPACE::stack;
	using NAMESPACE::vector;
	cout << "--- " + get_namespace() + "::stack benchmark ---\n";
	timespec tp1, tp2;
	stack<int, vector<int> > s1;
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 420000; i++)
		s1.push(i);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "420000 push: " << tp2 - tp1 << "s\n";
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	while (!s1.empty())
		s1.pop();
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "420000 pop: " << tp2 - tp1 << "s\n";
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 4200; i++)
		stack<int, vector<int> > s2(s1);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "4200 copy ctor: " << tp2 - tp1 << "s\n";
		stack<int, vector<int> > s2(s1);
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 4200; i++)
		stack<int, vector<int> > s2 = s1;
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "4200 copy operator: " << tp2 - tp1 << "s\n";
}

void map_tests()
{
	cout << "--- " + get_namespace() + "::map tests ---\n";
	using NAMESPACE::map;
	using NAMESPACE::pair;

	map<int, float> m;
	for (int i = -49; i < 410; i++)
		m[i] = 42.42 + i;
	m[0] = 0;
	display_range(m.begin(), m.end());
	display_range(m.rbegin(), m.rend());
	map<int, float> m3(m);
	map<int, float> m2(m.begin(), m.end());
	display_range(m2.begin(), m2.end());
	display_range(m3.begin(), m3.end());
	m3[-4200] = 5;
	display_range(m3.begin(), m3.end());
	std::cout << "empty: " << m3.empty() << '\n';
	std::cout << "size: " << m3.size() << '\n';
	m3.clear();
	m3.clear();
	std::cout << "empty: " << m3.empty() << '\n';
	std::cout << "size: " << m3.size() << '\n';
	m2 = m3;
	m3 = m;
	display_range(m2.begin(), m2.end());
	display_range(m3.begin(), m3.end());
	std::cout << "size: " << m3.size() << '\n';
		std::cout << '\n';
	std::cout << "max_size: " << m.max_size() << '\n';
	for (float i = 30; i < 40; i += .5)
	{
		pair<map<int, float>::iterator, bool> p = m.insert(pair<const int, float>((int)i, i));
		std::cout << "p.first: ";
		pair_display(*(p.first));
		std::cout << "p.second: " <<  p.second << '\n';
	}
	m2.insert(m.begin(), m.end());
	display_range(m2.begin(), m2.end());
	display_range(m3.begin(), m3.end());
	std::cout << "m2 size: " << m2.size() <<
		"\nm3 size: " << m3.size() << '\n';
	// NAMESPACE::swap(m2, m3);
	display_range(m2.begin(), m2.end());
	display_range(m3.begin(), m3.end());
	map<int, float> ok;
	for (int i = 0; i < 50; i++)
		ok[i] = 0.5 + i;
	display_range(ok.begin(), ok.end());
	std::cout << "deleting 5:\n";
	ok.erase(5);
	std::cout << "deleting 6:\n";
	ok.erase(ok.find(6));
	ok.clear();
	for (int i = 0; i < 10; i++)
		ok[i] = 0.5 + i;
	map<int, float>::iterator e1 = ok.end();
	e1--;
	map<int, float>::iterator e2 = e1;
	e2--; e2--;
	ok.erase(e2, e1);
	display_range(ok.begin(), ok.end());
	for (int i = -5; i < 15; i++)
		std::cout << ok.count(i) << ' ';
	std::cout << '\n';
	for (int i = -5; i < 15; i++)
	{
		map<int, float>::iterator it = ok.find(i);
		if (it != ok.end())
			std::cout << it->first << ' ' << it->second << ' ';
	}
	std::cout << '\n';
	typedef map<int, float>::iterator iter;
	pair<iter, iter> ub = ok.equal_range(5);
	display_range(ub.first, ub.second);
	pair<iter, iter> ub2 = m.equal_range(5);
	display_range(ub2.first, ub2.second); //uses lower_bound and upper_bound
}

void map_benchmark()
{
	using NAMESPACE::map;
	using NAMESPACE::pair;
	cout << "--- " + get_namespace() + "::map benchmark ---\n";
	timespec tp1, tp2;
	map<int, float> m1;
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 4200; i++)
		m1[i] = i + 0.01;
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "20000 []: " << tp2 - tp1 << "s\n";
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 20000; i++)
		m1.erase(i);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "20000 erase(): " << tp2 - tp1 << "s\n";
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 20000; i++)
		m1.insert(pair<const int, float>(i, i + 0.01));
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "20000 insert(): " << tp2 - tp1 << "s\n";
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 20000; i++)
		m1.find(i);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "20000 find(): " << tp2 - tp1 << "s\n";
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 20000; i++)
		m1.count(i);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "20000 count(): " << tp2 - tp1 << "s\n";
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (map<int, float>::iterator it = m1.begin(); it != m1.end(); it++);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "20000 iterations: " << tp2 - tp1 << "s\n";
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 5; i++)
		map<int, float> tmp(m1);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "5 * 20000 cpy ctr: " << tp2 - tp1 << "s\n";
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 2000; i++)
		m1.equal_range(i);
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "2000 equal_ranges: " << tp2 - tp1 << "s\n";
	map<int, float> tmp;
	clock_gettime(CLOCK_MONOTONIC, &tp1);
	for (int i = 0; i < 5; i++)
		tmp = m1;
	clock_gettime(CLOCK_MONOTONIC, &tp2);
	cout << "5 * 20000 operator=: " << tp2 - tp1 << "s\n";
}

int main( void )
{
	display_namespace();
	reverse_iterator_tests();
	is_integral_tests();
	equal_tests();
	lexicographical_tests();
	pair_tests();
	vector_tests();
	vector_benchmark();
	stack_tests();
	stack_benchmark();
	map_tests();
	map_benchmark();

	return (0);
}
