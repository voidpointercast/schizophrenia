/*
 * Character.cpp
 *
 *  Created on: Dec 2, 2012
 *      Author: voidpointercast
 */

#include<tuple>
#include<stdexcept>
#include<sstream>
#include<iterator>
#include<character/Character.hpp>

namespace schizohrenia {

	Character::Character(void)
	: boost::uuids::uuid(boost::uuids::random_generator()()),
	  CharacterType("") {

	}

	Character::Character(const std::string& type)
	: boost::uuids::uuid(boost::uuids::random_generator()()),
	  CharacterType(type) {

	}

	Character::~Character(void) {

	}


	std::string Character::getUUID(void) const {
		std::stringstream converter;
		std::copy(this->begin(),this->end(),std::ostream_iterator<uint8_t>(converter,""));
		return converter.str();
	}


	const std::vector<BasicTrait>& Character::getTraits(void) const {
		return this->CharacterTraits;
	}

	std::tuple<bool,std::string> Character::addTrait(const BasicTrait& trait) {
		auto checkResult = this->addTraitCheck(trait);
		if(std::get<0>(checkResult)) {
			this->CharacterTraits.push_back(trait);
		}
		return checkResult;
	}

	const std::vector<std::shared_ptr<Check<Character>>>& Character::getChecks(void) const {
		return this->CharacterChecks;
	}

	size_t Character::countTrait(const std::string& traitName) const {
		auto begin = this->CharacterTraits.begin();
		auto end   = this->CharacterTraits.end();
		return std::count_if(begin,end,[&traitName](const BasicTrait& trait) ->bool {return trait.Name == traitName;});
	}


	const BasicTrait& Character::operator[](const std::string& traitName) const {
		auto begin = this->CharacterTraits.begin();
		auto end   = this->CharacterTraits.end();
		auto result = std::find_if(begin,end,[&traitName](const BasicTrait& trait) ->bool { return trait.Name == traitName;});
		if(result == end) {
			throw std::runtime_error("Requested nonexisting trait <" + traitName + ">");
		}
		return *result;
	}


	void Character::addCheck(const std::shared_ptr<Check<Character> >& check) {
		this->CharacterChecks.push_back(check);
		auto begin 	= this->CharacterChecks.begin();
		auto end 	= this->CharacterChecks.end();
		if(check < this->CharacterChecks.back()) {
			std::sort(begin,end);
		}
	}
	void Character::removeCheck(typename std::vector<std::shared_ptr<Check<Character>>>::iterator position) {
		this->CharacterChecks.erase(position);
	}


	std::tuple<bool,std::string> Character::addAttribute(const BasicTrait& trait, const Attribute& attribute) {
		auto target = std::find(this->CharacterTraits.begin(),this->CharacterTraits.end(),trait);
		if(target == this->CharacterTraits.end()) {
			throw std::runtime_error("Cannot add attribute <" + attribute.Name + ">" +  " to nonexisting trait <" + trait.Name + ">");
		}
		auto checkResult = this->addAttributeCheck(trait,attribute);
		if(std::get<0>(checkResult)) {
			target->Attributes.push_back(attribute);
		}
		return checkResult;
	}

	std::tuple<bool,std::string> Character::setValue(const BasicTrait& trait, const std::string& value) {
		auto target = std::find(this->CharacterTraits.begin(),this->CharacterTraits.end(),trait);
		if(target == this->CharacterTraits.end()) {
			throw std::runtime_error("Cannot set value of nonexisting trait <" + trait.Name + ">");
		}
		auto checkResult = this->setValueCheck(trait,value);
			if(std::get<0>(checkResult)) {
				target->Value = value;
			}
			return checkResult;
		}

	std::tuple<bool,std::string> Character::setAttribute(const BasicTrait& trait, const Attribute& attribute, const std::string& value) {
		auto target = std::find(this->CharacterTraits.begin(),this->CharacterTraits.end(),trait);
		if(target == this->CharacterTraits.end()) {
			throw std::runtime_error("Cannot set attribute <" + attribute.Name + ">" +  " of nonexisting trait <" + trait.Name + ">");
		}
		auto attrTarget = std::find(target->Attributes.begin(),target->Attributes.end(),attribute);
		if(attrTarget == target->Attributes.end()) {
			throw std::runtime_error("Cannot set value of nonexisting attribute <" + attribute.Name + "> from trait <" + trait.Name + ">");
		}
		auto checkResult = this->setAttributeCheck(trait,attribute,value);
		if(std::get<0>(checkResult)) {
			attrTarget->setValue<std::string>(value);
		}
		return checkResult;
	}


	std::tuple<bool,std::string> Character::removeTrait(const BasicTrait& trait) {
		auto target = std::find(this->CharacterTraits.begin(),this->CharacterTraits.end(),trait);
		if(target == this->CharacterTraits.end()) {
			throw std::runtime_error("Cannot remove nonexisting trait <" + trait.Name +">");
		}
		auto checkResult = this->removeTraitCheck(trait);
		if(std::get<0>(checkResult)) {
			this->CharacterTraits.erase(target);
		}
		return checkResult;
	}

	std::tuple<bool,std::string> Character::removeAttribute(const BasicTrait& trait, const Attribute& attribute) {
		auto target = std::find(this->CharacterTraits.begin(),this->CharacterTraits.end(),trait);
		if(target == this->CharacterTraits.end()) {
			throw std::runtime_error("Cannot remove attribute <" + attribute.Name + ">" +  " from nonexisting trait <" + trait.Name + ">");
		}
		auto attrTarget = std::find(target->Attributes.begin(),target->Attributes.end(),attribute);
		if(attrTarget == target->Attributes.end()) {
			throw std::runtime_error("Cannot remove nonexisting attribute <" + attribute.Name + "> from trait <" + trait.Name + ">");
		}
		auto checkResult = this->removeAttributeCheck(trait,attribute);
		if(std::get<0>(checkResult)) {
			target->Attributes.erase(attrTarget);
		}
		return checkResult;
	}

	YAML::Emitter& Character::operator<<(YAML::Emitter& out) const {
			out << YAML::BeginDoc << YAML::BeginSeq << YAML::Binary(this->data,sizeof(uint8_t)*16);
			out << YAML::BeginMap << YAML::Key << "BasicTraits" << YAML::Value << this->CharacterTraits;
			out << YAML::EndMap << YAML::EndSeq << YAML::EndDoc;
			return out;
	}

	YAML::Iterator Character::operator>>(YAML::Iterator in) {
		
		
		return in;
	}



	std::ostream& Character::serialize(std::ostream& out, const SupportedSerialization type) {
		return out;
	}

//Protected


	std::tuple<bool,std::string> Character::addAttributeCheck(const BasicTrait& trait, const Attribute& attribute)  const {
		return this->check([&](const std::shared_ptr<Check<Character> >& check) -> std::tuple<Check<Character>::Result,std::string> { return check->operator()(trait,attribute,Check<Character>::Action::Add);});
	}

	std::tuple<bool,std::string> Character::addTraitCheck(const BasicTrait& trait) const {
		return this->check([&](const std::shared_ptr<Check<Character>>& check) -> std::tuple<Check<Character>::Result,std::string> { return check->operator()(trait,Check<Character>::Action::Add);});
	}

	std::tuple<bool,std::string> Character::removeTraitCheck(const BasicTrait& trait) const {
		return this->check([&](const std::shared_ptr<Check<Character>>& check) -> std::tuple<Check<Character>::Result,std::string> { return check->operator()(trait,Check<Character>::Action::Remove);});
	}

	std::tuple<bool,std::string> Character::removeAttributeCheck(const BasicTrait& trait, const Attribute& attribute) const {
		return this->check([&](const std::shared_ptr<Check<Character>>& check) -> std::tuple<Check<Character>::Result,std::string> { return check->operator()(trait,attribute,Check<Character>::Action::Remove);});
	}

	std::tuple<bool,std::string> Character::setValueCheck(const BasicTrait& trait, const std::string& value)  const{
		return this->check([&](const std::shared_ptr<Check<Character>>& check) -> std::tuple<Check<Character>::Result,std::string> { return check->operator()(trait,value);});
	}

	std::tuple<bool,std::string> Character::setAttributeCheck(const BasicTrait& trait, const Attribute& attribute, const std::string& value)  const{
		return this->check([&](const std::shared_ptr<Check<Character>>& check) -> std::tuple<Check<Character>::Result,std::string> { return check->operator()(trait,attribute,value);});
	}


}


