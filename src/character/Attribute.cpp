/*
 * Attribute.cpp
 *
 *  Created on: Dec 2, 2012
 *      Author: voidpointercast
 */

#include "Attribute.hpp"

namespace schizophrenia {

	Attribute::Attribute(const std::string& name, const std::string& value)
	: Name(name),
	  Value(value) {

	}


	Attribute::~Attribute() {
		// TODO Auto-generated destructor stub
	}

	bool Attribute::operator<(const Attribute& right) const {
		return this->Name < right.Name;
	}

	bool Attribute::operator==(const Attribute& right) const {
		return this->Name == right.Name;
	}

	const std::string& Attribute::getCategory(void) const {
		return this->Category;
	}


	YAML::Emitter& Attribute::operator<<(YAML::Emitter& out) const {
		out << YAML::BeginMap;
		out << YAML::Key << "name" << YAML::Value << this->Name;
		out << YAML::Key << "value" << YAML::Value << this->Value;
		out << YAML::Key << "category" << YAML::Value << this->Category;
		out << YAML::Key << "keywords" << YAML::Value;
		out << YAML::BeginSeq;
		std::for_each(this->Keywords.begin(), this->Keywords.end(), [&](const std::string& key) -> void { out << key; });
		out << YAML::EndSeq;
		out << YAML::EndMap;
		return out;
	}

	YAML::Iterator Attribute::operator>>(YAML::Iterator in) {
		*in->FindValue("name")  >> this->Name;
		*in->FindValue("value") >> this->Value;
		*in->FindValue("category") >> this->Category;
		*in->FindValue("keywords") >> this->Keywords;
		return in++;
	}

}
