//
// Created by Alvaro Diaz on 25-11-21.
//

#include "date.h"

#include <cmath>
#include <sstream>

namespace qcode {
    namespace time {
        Date::Date(const Date& otherDate)
        {
            _day = otherDate.day();
            _month = otherDate.month();
            _year = otherDate.year();
        }

        Date::Date(int d, int m, long y)
        {
            if (_validate(d, m, y))
            {
                _day = d;
                _month = m;
                _year = y;
                return;
            }
            else
            {
                throw std::invalid_argument("Invalid day, month and year");
            }
        }

        Date::Date(const std::string& stringDate)
        {
            if (stringDate.length() != 10)
                throw std::invalid_argument("String has invalid length should be yyyy/mm/dd");
            int d, m, y;
            try
            {
                d = stoi(stringDate.substr(8, 2));
                m = stoi(stringDate.substr(5, 2));
                y = stoi(stringDate.substr(0, 4));
            }
            catch (...)
            {
                throw std::invalid_argument("Invalid day, month and year");
            }
            if (_validate(d, m, y))
            {
                _day = d;
                _month = m;
                _year = y;
                return;
            }
            else
            {
                throw std::invalid_argument("Invalid day, month and year");
            }

        }

        Date::Date(long excelSerial)
        {
            _setDateFromExcelSerial(excelSerial);
        }

        bool Date::operator<(const Date& rhs) const
        {
            return this->excelSerial() < rhs.excelSerial();
        }

        bool Date::operator>(const Date& rhs) const
        {
            return this->excelSerial() > rhs.excelSerial();
        }

        bool Date::operator<=(const Date& rhs) const
        {
            return this->excelSerial() <= rhs.excelSerial();
        }

        bool Date::operator>=(const Date& rhs) const
        {
            return this->excelSerial() >= rhs.excelSerial();
        }

        bool Date::operator==(const Date& rhs) const
        {
            return this->excelSerial() == rhs.excelSerial();
        }

        bool Date::operator!=(const Date& rhs) const
        {
            return this->excelSerial() != rhs.excelSerial();
        }

        int Date::day() const
        {
            return _day;
        }

        int Date::month() const
        {
            return _month;
        }

        long Date::year() const
        {
            return _year;
        }

        long long int Date::excelSerial() const
        {
            // Excel/Lotus 123 have a bug with 29-02-1900. 1900 is not a
            // leap year, but Excel/Lotus 123 think it is...
            if ((_day == 29)&&(_month == 2)&&(_year == 1900))
                return 60;

            // DMY to Modified Julian calculate with an extra subtraction of 2415019.
            long nSerialDate =
                    int(( 1461 * ( _year + 4800 + int(( _month - 14 ) / 12) ) ) / 4) +
                    int(( 367 * ( _month - 2 - 12 * ( ( _month - 14 ) / 12 ) ) ) / 12) -
                    int(( 3 * ( int(( _year + 4900 + int(( _month - 14 ) / 12) ) / 100) ) ) / 4) +
                    _day - 2415019 - 32075;

            if (nSerialDate <= 60)
            {
                //Aqui hay que poner <=60
                // Because of the 29-02-1900 bug, any serial date
                // under 60 is one off... Compensate.
                nSerialDate--;
            }

            return (int)nSerialDate;

        }

        long Date::dayDiff(const Date& otherDate) const
        {
            return otherDate.excelSerial() - this->excelSerial();
        }

        Date Date::addDays(long nDays) const
        {
            long newSerial = this->excelSerial() + nDays;
            return Date {newSerial};
        }

        bool Date::isEndOfMonth() const
        {
            if (this->addDays(1).month() != this->month())
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        Date Date::addMonths(long nMonths) const
        {
            //Equivalent to Excel Function EDATE()
            //adds nMonths (number of months) to this for positive/negative values of nMonths

            int dm[13];

            dm[1] = 31;
            dm[2] = 28;
            dm[3] = 31;
            dm[4] = 30;
            dm[5] = 31;
            dm[6] = 30;
            dm[7] = 31;
            dm[8] = 31;
            dm[9] = 30;
            dm[10] = 31;
            dm[11] = 30;
            dm[12] = 31;

            bool eom = false;

            int d = _day;
            int m = _month;
            long y = _year;

            if ((d == dm[m]) && (m != 2))
            {
                eom = true;  //Detect if the date corresponds to the end of a month
            }

            //Aquí hay que arreglar la addMonths
            nMonths += m;

            auto aux = (int)floor((double)nMonths / 12.0);
            m = nMonths - 12 * aux;

            if (m == 0)
                m = 12;

            aux = (int)floor((double)(nMonths - 1) / 12.0);
            y = y + aux;

            if (y < 0)
                y = 1900;

            if (d > dm[m])
                eom = true;

            if (eom)
            {
                if (d > dm[m])
                    d = dm[m];
                if (((y / 4) == (y / 4.0)) && (m == 2))
                    d = 29;
            }

            return Date {d, m, y};
        }

        Date::WeekDay Date::weekDay() const
        {
            static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
            auto auxYear = _year - (_month < 3);
            return WeekDay((auxYear + auxYear/4 - auxYear/100 + auxYear/400 + t[_month-1] + _day) % 7);
        }

        std::string Date::isoFormat() const
        {
            std::stringstream ss;
            std::string auxDay = "";
            std::string auxMonth = "";
            if (_day < 10) { auxDay = "0"; }
            if (_month < 10) { auxMonth = "0"; }
            ss << _year << "-" << auxMonth << _month << "-" << auxDay << _day;
            return ss.str();
        }

        // Private methods
        bool Date::_validate(int d, int m, long y)
        {
            if ((d < 1) || (d > 31))
            {
                return false;
            }

            if ((m < 1) || (m > 12))
            {
                return false;
            }

            if (y < 1)
            {
                return false;
            }

            if ((d == 29) && (m == 2))
            {
                return ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
            }

            if (m == 2 && (d == 30 || d == 31))
            {
                throw std::invalid_argument("Invalid day for month = 2");
            }
            bool dayMonth = (d == 31) && ((m == 2) || (m == 4) || (m == 6) || (m == 9) || (m == 11));
            return !dayMonth;

        }

        void Date::_setDateFromExcelSerial(long excelSerial)
        {
            // Excel/Lotus 123 have a bug with 29-02-1900. 1900 is not a
            // leap year, but Excel/Lotus 123 think it is...
            if (excelSerial == 60)
            {
                _day = 29;
                _month = 2;
                _year = 1900;

                return;
            }
            else if (excelSerial < 60)
            {
                // Because of the 29-02-1900 bug, any serial date
                // under 60 is one off... Compensate.
                excelSerial++;
            }

            // Modified Julian to DMY calculation with an addition of 2415019
            long l = excelSerial + 68569 + 2415019;
            int n = int(( 4 * l ) / 146097);
            l = l - ( 146097 * n + 3 ) / 4;
            int i = int(( 4000 * ( l + 1 ) ) / 1461001);
            l = l - ( 1461 * i ) / 4 + 31;
            int j = int(( 80 * l ) / 2447);
            _day = l - int(( 2447 * j ) / 80);
            l = int(j / 11);
            _month = j + 2 - ( 12 * l );
            _year = 100 * ( n - 49 ) + i + l;
        }

    }
}

