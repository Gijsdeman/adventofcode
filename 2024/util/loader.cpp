#include "util.h"
#include <functional>
#include <iostream>
#include <map>

util::DayFactory &util::DayFactory::instance() {
  static DayFactory factory;
  return factory;
}

void util::DayFactory::registerDay(const std::string &day, Creator creator) {
  creators_[day] = std::move(creator);
}

util::Day *util::DayFactory::createDay(const std::string &day) {
  if (const auto it = creators_.find(day); it != creators_.end()) {
    return it->second();
  }
  return nullptr;
}

util::Day *util::loadDayInstance(const std::string &day) {
  return DayFactory::instance().createDay(day);
}

util::DayRegistrar::DayRegistrar(const std::string &day,
                                 const DayFactory::Creator &creator) {
  DayFactory::instance().registerDay(day, creator);
}