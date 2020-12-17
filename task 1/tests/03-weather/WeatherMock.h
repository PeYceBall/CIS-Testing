//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#pragma once

#include <Weather.h>
#include <gmock/gmock.h>

class WeatherMock : public Weather {
public:
  MOCK_METHOD(cpr::Response, Get, (const std::string &city), (override));
};
