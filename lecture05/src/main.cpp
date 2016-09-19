#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "lecture05/exercise01/product.h"

#define PRODUCT_DB_FILE	"product.db"

using namespace exercise01;

/*
 * Read products from file
 */
void productDBRead(ProductList& pl, const std::string& fileName) {
	pl.clear();
	std::ifstream s(fileName.c_str());

	if (!s.good()) return;
	std::istream_iterator<Product> start(s);
	std::istream_iterator<Product> eof;
	std::copy(start, eof, std::back_inserter(pl));
}


/**
 * Printout all products
 */
void printAll(const ProductList& pl) {
	std::cout << "##################################################" << std::endl;
	std::cout << "Printing out all products..." << std::endl;
	std::cout << "----------------------------" << std::endl;

	std::ostream_iterator<Product> print(std::cout, "\n");
	std::copy(pl.begin(), pl.end(), print);

	std::cout << "##################################################" << std::endl;
}


/*
 * Add item
 */
void addItem(ProductList& pl) {
	std::cout << "##################################################" << std::endl;
	std::cout << "Add item" << std::endl;
	std::cout << "----------------------------" << std::endl;

	std::string name;
	float price;
	int sold;

	std::cout << "Enter name: " << std::endl;
	std::cin >> name;

	std::cout << "Enter price: " << std::endl;
	std::cin >> price;

	std::cout << "Enter amount sold: " << std::endl;
	std::cin >> sold;

	pl.push_back(Product(name, price, sold));

	/*
	std::istream_iterator<Product> input(std::cin);
	std::istream_iterator<Product> eos;
	std::copy(input, eos, std::back_inserter(pl));
	*/

	std::cout << "##################################################" << std::endl;
}


/*
 * Write data to db file
 */
void productDBWrite(const ProductList& pl, const std::string& fileName) {
	std::ofstream s(fileName.c_str());

	if (!s.good()) return;
	std::ostream_iterator<Product> out(s, "\n");
	std::copy(pl.begin(), pl.end(), out);
}


/*
 * Print poorly selling products
 */
void printPoorlySellingProducts(const ProductList& pl) {
	std::cout << "##################################################" << std::endl;
	std::cout << "Poorly selling products" << std::endl;
	std::cout << "----------------------------" << std::endl;

	std::ostream_iterator<Product> out(std::cout, "\n");
	std::remove_copy_if(pl.begin(), pl.end(), out, [](Product p){ return p.sold() > 10; });

	std::cout << "##################################################" << std::endl;
}


/*
 * Set a discount on all products - Using for_each()
 */
void addDiscountUsingForEach(ProductList& pl) {
	int discount;

	std::cout << "Enter discount: " << std::endl;
	std::cin >> discount;

	std::for_each(pl.begin(), pl.end(), [discount](Product& p){ p.setPrice(p.price() - (p.price()*discount/100)); });
}


/*
 * Set a discount on all products - Using transform()
 */
void addDiscountUsingTransform(ProductList& pl)
{
	int discount;

	std::cout << "Enter discount: " << std::endl;
	std::cin >> discount;

	std::transform(pl.begin(), pl.end(), pl.begin(), [discount](Product p){ return Product(p.name(), p.price()-(p.price()*discount/100), p.sold()); });
}


void addDiscountUsingSetDiscount(ProductList& pl) {
	int discount;

	std::cout << "Enter discount: " << std::endl;
	std::cin >> discount;

	for (Product& p : pl)
		p.setDiscount(discount);
}

/*
 * Calculate the total amount of sold products
 */
void calcTotalSoldProducts(ProductList& pl) {
	std::vector<unsigned int> sold;
	std::transform(pl.begin(), pl.end(), std::back_inserter(sold), std::mem_fun_ref(&Product::price));

	std::cout << "##################################################" << std::endl;
	std::cout << "Total amount of sold products" << std::endl;
	std::cout << "----------------------------" << std::endl;

	std::cout << std::accumulate(sold.begin(), sold.end(), 0) << std::endl;

	std::cout << "##################################################" << std::endl;
}


/*
 * Setting discount using bind2nd - OPTIONAL
 */


int main() {
	bool running = true;
	ProductList pl;

	while (running) {
		char choice;

		std::cout << "********************" << std::endl;
		std::cout << "Help menu: " << std::endl;
		std::cout << "'1' Read product database" << std::endl;
		std::cout << "'2' Print all items" << std::endl;
		std::cout << "'3' Add item" << std::endl;
		std::cout << "'4' Write product database" << std::endl;
		std::cout << "'5' Print poorly selling products" << std::endl;
		std::cout << "'6' Set a discount on all products (using for_each() )" << std::endl;
		std::cout << "'7' Set a discount on all products (using transform() )" << std::endl;
		std::cout << "'8' Calculate the total amount of sold products" << std::endl;
		std::cout << "'9' Set a discount on all products (using addDiscount() )" << std::endl;


		std::cout << "'q' Quit" << std::endl;
		std::cout << "Your choice: ";
		std::cin >> choice;

		switch (choice) {
			case '1':
				productDBRead(pl, PRODUCT_DB_FILE);
				break;

			case '2':
				printAll(pl);
				break;

			case '3':
				addItem(pl);
				break;

			case '4':
				productDBWrite(pl, PRODUCT_DB_FILE);
				break;

			case '5':
				printPoorlySellingProducts(pl);
				break;

			case '6':
				addDiscountUsingForEach(pl);
				break;

			case '7':
				addDiscountUsingTransform(pl);
				break;

			case '8':
				calcTotalSoldProducts(pl);
				break;

			case '9':
				addDiscountUsingSetDiscount(pl);
				break;

			case 'q':
			case 'Q':
				running = false;
		}


	}
}