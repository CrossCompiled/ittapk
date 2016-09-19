#ifndef EXERCISE01_PRODUCT_H
#define EXERCISE01_PRODUCT_H

#include <iostream>
#include <vector>
#include <string>

namespace exercise01 {
		class Product {
		public:
				Product(const std::string& name, float price, unsigned int sold = 0)
								: name_(name), price_(price), sold_(sold) {}

				Product()
								: name_(""), price_(0), sold_(0) {}

				const std::string& name() const {
					return name_;
				}

				float price() const {
					return price_;
				}

				void setPrice(float newPrice) {
					price_ = newPrice;
				}

				void setDiscount(int percent) {
					price_ = price_ - (price_ * percent / 100);
				}

				unsigned int sold() const {
					return sold_;
				}

				friend std::istream& operator>>(std::istream& i, Product& p);

				friend std::ostream& operator<<(std::ostream& o, const Product& p);

		private:
				std::string name_;
				float price_;
				int sold_;
		};

		typedef std::vector<Product> ProductList;

		std::ostream& operator<<(std::ostream& o, const Product& p) {
			return o << p.name_ << " " << p.price_ << " " << p.sold_;
		}

		std::istream& operator>>(std::istream& i, Product& p) {
			return i >> p.name_ >> p.price_ >> p.sold_;
		}
}

#endif