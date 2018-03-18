//
// File: Pool.test.cpp
//

#define BOOST_TEST_MODULE PoolTest
#include <boost/test/unit_test.hpp>

#include "Pool.h"
#include <stdexcept>

/// Это так называемый Test Fixture, который отвечает за создание и удаление
/// объекта перед каждым Test Case или Test Suite.
struct FilterFixture {
  std::string testData{"1.16.37.242\t?\t?\n"
                       "8.8.4.4\t    ?\t?\n"
                       "1.15.88.38\t ?\t?\n"
                       "12.52.1.105\t?\t?\n"
                       "162.37.1.53\t?\t?\n"
                       "73.22.37.37\t?\t?\n"
                       "12.52.73.36\t?\t?\n"};
  std::istringstream iss{testData};
  Pool pool{iss};
};

/// Данный тест проверяет корректность создания объекта Pool, где данные
/// разбираются на этапе инициализации объекта. Для проверки корректности
/// проверяются входные и выходные данные, которые предствлены ввиде строк.
///
/// Тест потребует написание конструктора класса Pool, который обрабатывает
/// поток входящих данных и сортирует данные в обратном лексикографическом
/// порядке. Также для проверки корректности работы нужно реализовать
/// оператор '<<' для 'std::osteream', чтобы получить выходные данные.
BOOST_AUTO_TEST_CASE(PoolCreate) {
  std::string testData{"10.23.71.73\tAny\tText\n"
                       "11.51.32.23\t?1\t..\n"
                       "56.72.88.14\t0..0\tOMG\n"
                       "2.63.82.227\t45\tM64\n"};
  std::string result{"56.72.88.14\n"
                     "11.51.32.23\n"
                     "10.23.71.73\n"
                     "2.63.82.227\n"};

  std::istringstream iss(testData);
  std::ostringstream oss;

  Pool pool{iss};
  oss << pool;

  BOOST_CHECK_EQUAL(oss.str(), result);
}

/// В задании ничего не сказано об обработке некорретных входных данных.
/// Поэтому решение данной проблемы передаётся разработчику. Моё решение этой
/// проблемы будет простым - бросать исключение `std::runtime_error`.
///
/// Если бы не внешние входные данные, то можно было бы делать проверки через
/// `assert`, чтобы проверять корректность входных данных.

/// Не корректные входные данные: "Октет больше 255"
BOOST_AUTO_TEST_CASE(PoolCreateNotCorrect_OctetGreater) {
  std::string testData{"70.128.1620.3\t?\t?\n"};
  std::istringstream iss(testData);

  BOOST_CHECK_THROW(Pool{iss}, std::runtime_error);
}

/// Не корректные входные данные: "Октет меньше 0"
BOOST_AUTO_TEST_CASE(PoolCreateNotCorrect_OctetLess) {
  std::string testData{"70.128.162.-3\t?\t?\n"};
  std::istringstream iss(testData);

  BOOST_CHECK_THROW(Pool{iss}, std::runtime_error);
}

/// Не корректные входные данные: "Пропущен один из четырёх октетов"
BOOST_AUTO_TEST_CASE(PoolCreateNotCorrect_OctetLost) {
  std::string testData{"70.128.162\t?\t?\n"};
  std::istringstream iss(testData);

  BOOST_CHECK_THROW(Pool{iss}, std::runtime_error);
}

/// Не корректные входные данные: "Пропущен один из четырёх октетов
/// и получение конца потока (EOF)"
BOOST_AUTO_TEST_CASE(PoolCreateNotCorrect_OctetLostBreak) {
  std::string testData{"70.128"};
  std::istringstream iss(testData);

  BOOST_CHECK_THROW(Pool{iss}, std::runtime_error);
}

/// Приступаем к разработке функций фильтрации адресов. Требование первое:
/// Создаём у Pool метод `filter`, который принимает 2 аргумента:
/// значение первого октета и поток для вывода (по умолчанию std::cout).
BOOST_FIXTURE_TEST_CASE(PoolFilter_OneArgument, FilterFixture) {
  std::ostringstream oss{};
  std::string result("1.16.37.242\n"
                     "1.15.88.38\n");

  pool.filter(1, oss);

  BOOST_CHECK_EQUAL(oss.str(), result);
}

/// Идём по пути наименьшего сопротивления. Пишем тесты, чтобы они проходили.
/// Второе требование: фильтрация по двум первым октетам. Для этого мы просто
/// перегрузим метод filter с тремя аргументами: два октета и поток.
BOOST_FIXTURE_TEST_CASE(PoolFilter_TwoArguments, FilterFixture) {
  std::ostringstream oss{};
  std::string result("12.52.73.36\n"
                     "12.52.1.105\n");

  pool.filter(12, 52, oss);

  BOOST_CHECK_EQUAL(oss.str(), result);
}

/// Осталось проверить третье требование: фильтрация по любому октету.
BOOST_FIXTURE_TEST_CASE(PoolFilter_Any, FilterFixture) {
  std::ostringstream oss{};
  std::string result("162.37.1.53\n"
                     "73.22.37.37\n"
                     "1.16.37.242\n");

  pool.filter_any(37, oss);

  BOOST_CHECK_EQUAL(oss.str(), result);
}
