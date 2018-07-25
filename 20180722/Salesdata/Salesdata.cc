#include "Salesdata.h"

Sales_data::Sales_data():book_NO("0000"),unit_sold(0),revenue(0) {}

Sales_data::Sales_data(const std::string isbn, unsigned int units, float price):book_NO(isbn),unit_sold(units),revenue(units*price) {}

Sales_data::Sales_data(const Sales_data &book):book_NO(book.book_NO),unit_sold(book.unit_sold),revenue(book.revenue) {}

Sales_data Sales_data::add(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

Sales_data& Sales_data::combine(const Sales_data &book)
{
	if(book_NO == book.book_NO)
	{
		unit_sold += book.unit_sold;
		revenue = book.revenue;
		return *this;
	}
	return *this;
}

std::string Sales_data::isbn() const
{
	return book_NO;
}

float Sales_data::average() const
{
	return revenue/unit_sold;
}

Sales_data& Sales_data::operator=(const Sales_data &book)
{
	book_NO = book.book_NO;
	unit_sold = book.unit_sold;
	revenue = book.revenue;
	return *this;
}

std::istream &read(std::istream &in, Sales_data &item)
{
	float price = 0;
	in >> item.book_NO >> item.unit_sold >> price;
	item.revenue = price * item.unit_sold;
	return in;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
	os << item.book_NO << " " << item.unit_sold << " " << item.revenue
		<< item.average() << std::endl;
	return os;
}
