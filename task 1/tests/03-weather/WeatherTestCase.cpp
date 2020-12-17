//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherTestCase.h"
#include "WeatherMock.h"

#include <fstream>
#include <sstream>

using ::testing::AtLeast;
using ::testing::Return;

const std::string london_response_path =
    "../tests/03-weather/response_london.json";
const std::string paris_response_path =
    "../tests/03-weather/response_paris.json";

cpr::Response MakeResponse(const std::string &file_path, int status_code) {
  std::ifstream file(file_path);
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();

  std::string file_content = buffer.str();
  return {status_code, std::move(file_content), cpr::Header(), "",
          1.00,        cpr::Cookies(),          cpr::Error()};
}

TEST(WeatherTestCase, BadStatusCode) {
  WeatherMock mock;
  auto response = MakeResponse(london_response_path, 404);
  EXPECT_CALL(mock, Get).Times(AtLeast(1)).WillOnce(Return(response));

  EXPECT_THROW(mock.GetResponseForCity("London"), std::invalid_argument);
}

TEST(WeatherTestCase, GetResponseForCitySuccess) {
  WeatherMock mock;
  auto response = MakeResponse(london_response_path, 200);
  EXPECT_CALL(mock, Get).Times(AtLeast(1)).WillOnce(Return(response));

  json expected = json::parse(response.text);
  json actual = mock.GetResponseForCity("London");
  EXPECT_EQ(expected, actual);
}

TEST(WeatherTestCase, GetTemperatureLondon) {
  WeatherMock mock;
  auto response = MakeResponse(london_response_path, 200);
  EXPECT_CALL(mock, Get).Times(AtLeast(1)).WillOnce(Return(response));

  float expected = 10.;
  float actual = mock.GetTemperature("London");
  EXPECT_FLOAT_EQ(expected, actual);
}

TEST(WeatherTestCase, FindDifferenceBetweenTwoCities) {
  WeatherMock mock;
  auto response_london = MakeResponse(london_response_path, 200);
  auto response_paris = MakeResponse(paris_response_path, 200);

  EXPECT_CALL(mock, Get)
      .Times(AtLeast(2))
      .WillOnce(Return(response_london))
      .WillOnce(Return(response_paris));

  float expected = 10. - 20.;
  float actual = mock.FindDiffBetweenTwoCities("London", "Paris");
  EXPECT_FLOAT_EQ(expected, actual);
}

TEST(WeatherTestCase, GetDifferenceStringPositive) {
  WeatherMock mock;
  auto response_london = MakeResponse(london_response_path, 200);
  auto response_paris = MakeResponse(paris_response_path, 200);

  EXPECT_CALL(mock, Get)
      .Times(AtLeast(2))
      .WillOnce(Return(response_paris))
      .WillOnce(Return(response_london));

  std::string expected =
      "Weather in Paris is warmer than in London by 10 degrees";
  std::string actual = mock.GetDifferenceString("Paris", "London");
  EXPECT_EQ(expected, actual);
}

TEST(WeatherTestCase, GetDifferenceStringNegative) {
  WeatherMock mock;
  auto response_london = MakeResponse(london_response_path, 200);
  auto response_paris = MakeResponse(paris_response_path, 200);

  EXPECT_CALL(mock, Get)
      .Times(AtLeast(2))
      .WillOnce(Return(response_london))
      .WillOnce(Return(response_paris));

  std::string expected =
      "Weather in London is colder than in Paris by 10 degrees";
  std::string actual = mock.GetDifferenceString("London", "Paris");
  EXPECT_EQ(expected, actual);
}

TEST(WeatherTestCase, SetApiKey) {
  WeatherMock mock;
  EXPECT_NO_THROW(mock.SetApiKey("key"));
}