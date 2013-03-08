#include<character/BasicTrait.hpp>



namespace schizophrenia {

	BasicTrait::BasicTrait(const std::string& name, const std::string& value)
	: Value(value), Attributes(size_t(0)), Name(name), ID(name)  {

	}
	
	BasicTrait::BasicTrait(const std::string& id, const std::string& name, const std::string& value)
	: Value(value), Attributes(size_t(0)), Name(name), ID(id)  {

	}

	BasicTrait::~BasicTrait(void) {

}

	bool BasicTrait::operator<(const BasicTrait& right) const{
		return this->Name < right.Name;
	}


	bool BasicTrait::operator==(const BasicTrait& right) const{
		return this->ID == right.ID && this->Attributes == right.Attributes;
	}

	bool BasicTrait::operator==(const std::string& right) const{
			return this->ID == right;
	}


	bool BasicTrait::hasAttribute(const std::string& attribute) const {
		auto begin = this->Attributes.begin();
		auto end   = this->Attributes.end();
		return std::find_if(begin,end,[&attribute](const Attribute& attr)->bool {return attr.Name == attribute;}) != this->Attributes.end();
	}
	
	bool BasicTrait::hasAttribute(const Attribute& attribute) const {
		auto begin = this->Attributes.begin();
		auto end   = this->Attributes.end();
		return std::find(begin,end,attribute) != this->Attributes.end();
	}

	YAML::Emitter& BasicTrait::operator<<(YAML::Emitter& out) const {
		out << YAML::BeginMap;
		out << YAML::Key << "id" << YAML::Value << this->ID;
		out << YAML::Key << "name" << YAML::Value << this->Name;
		out << YAML::Key << "value"<< YAML::Value << this->Value;
		out << YAML::Key << "attributes" << YAML::Value << this->Attributes;
		out << YAML::EndMap;
		return out;
	}

	YAML::Iterator BasicTrait::operator>>(YAML::Iterator in) {
		*in->FindValue("id")    >> this->ID;
		*in->FindValue("name")	>> this->Name;
		*in->FindValue("value") >> this->Value;
		const YAML::Node* attributes = in->FindValue("attributes");
		Attribute buffer;
		for(YAML::Iterator attr=attributes->begin(); attr != attributes->end(); ++ attr) {
			attr >> buffer;
			this->Attributes.push_back(buffer);
		}
		return in++;
	}



}
