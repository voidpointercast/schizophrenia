/*
 * Attribute.cpp
 *
 *  Created on: Dec 2, 2012
 *      Author: voidpointercast
 */

#include "Attribute.hpp"

namespace schizohrenia {

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

	YAML::Emitter& Attribute::operator<<(YAML::Emitter& out) const {
		out << YAML::BeginMap;
		out << YAML::Key << "name" << YAML::Value << this->Name;
		out << YAML::Key << "value" << YAML::Value << this->Value;
		out << YAML::EndMap;
		return out;
	}

	YAML::Iterator Attribute::operator>>(YAML::Iterator in) {
		*in->FindValue("name")  >> this->Name;
		*in->FindValue("value") >> this->Value;
		return in++;
	}

}
