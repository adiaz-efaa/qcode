//
// Created by Alvaro Diaz on 25-11-21.
//

#ifndef QCODE_DATE_H
#define QCODE_DATE_H


#include <iostream>
#include <string>

/*!
 * @brief Date es la implementación de QCode de una clase para manejar fechas
 * @author Alvaro Díaz (QCode)
 * @version 1.0
 * @date Abril, 2020
 */

namespace qcode {
    namespace time {
        class Date
        {
        public:

            /*!
             * WeekDay es un enum que sirve para identificar los días de la semana.
             */
            enum WeekDay
            {
                monday = 1,
                tuesday = 2,
                wednesday = 3,
                thursday = 4,
                friday = 5,
                saturday = 6,
                sunday = 0
            };

            /*!
             * Constructor por default inhabilitado
             */
            Date() = delete;

            /*!
             * Constructor
             * @param excelSerial (long) representación de Excel de una fecha
             * @return un objeto QCDate con la fecha indicada por excelSerial
             */
            explicit Date(long excelSerial);

            /*!
             * Constructor
             * @param d día
             * @param m mes
             * @param y año
             * @return un objeto QCDate con la fecha d/m/y
             */
            Date(int d, int m, long y);

            /*!
            * Constructor
            * @param stringDate yyyy/mm/dd o yyyy-mm-dd
            * @return un objeto QCDate con la fecha d/m/y
            */
            explicit Date(const std::string& stringDate);

            /*!
             * Copy constructor
             * @param otherDate otro objeto de tipo QCDate
             * @return objeto QCDate receptor de la copia
             */
            Date(const Date& otherDate);

            /*!
             * Operator= sobrecarga (assigment operator)
             * @param otherDate
             */
            Date& operator=(const Date& otherDate) = default;

            /*!
             * Operator < sobrecarga
             * @param rhs
             * @return (bool)
             */
            bool operator<(const Date& rhs) const;

            /*!
             * Operator > sobrecarga
             * @param rhs
             * @return (bool)
             */
            bool operator>(const Date& rhs) const;

            /*!
             * Operator <= sobrecarga
             * @param rhs
             * @return (bool)
             */
            bool operator<=(const Date& rhs) const;

            /*!
             * Operator >= sobrecarga
             * @param rhs
             * @return (bool)
             */
            bool operator>=(const Date& rhs) const;

            /*!
             * Operator == sobrecarga
             * @param rhs
             * @return (bool)
             */
            bool operator==(const Date& rhs) const ;

            /*!
             * Operator != sobrecarga
             * @param rhs
             * @return (bool)
             */
            bool operator!=(const Date& rhs) const ;

            long operator-(const Date& rhs) const
            {
                return -dayDiff(rhs);
            }

            friend std::ostream& operator<<(std::ostream& os, const Date& dt)
            {
                os << dt.isoFormat();
                return os;
            }

            /*!
             * Getter
             * @return (int) el día de la fecha
             */
            [[nodiscard]] int day() const;

            /*!
             * Getter
             * @return (int) el mes de la fecha
             */
            [[nodiscard]] int month() const;

            /*!
             * Getter
             * @return (int) el año de la fecha
             */
            [[nodiscard]] long year() const;

            /*!
             * @return (int) Retorna la fecha como su representación en Excel
             */
            [[nodiscard]] long long int excelSerial() const;

            /*!
             * Calcula el número de días reales entre otherDate y si misma
             * Será > 0 si otherDate es mayor que si misma.
             * @param otherDate
             * @return (long) número de días calculados
             */
            [[nodiscard]] long dayDiff(const Date& otherDate) const;

            /*!
             * Calcula la fecha que resulta de sumar un número de días a si misma
             * @param nDays número de días a sumar
             * @return (QCDate) fecha resultante
             */
            [[nodiscard]] Date addDays(long nDays) const;

            /*!
            * Indica si la fecha corresponde al último día del mes.
            * @return (bool) true si es el último día del mes, false en los otros casos.
            */
            [[nodiscard]] bool isEndOfMonth() const;

            /*!
             * Calcula la fecha que resulta de sumar un número de meses a si misma
             * @param nMonths número de meses a sumar
             * @return (QCDate) fecha resultante
             */
            [[nodiscard]] Date addMonths(long nMonths) const;

            /*!
             * Retorna el día de la semana
             * @return (QCWeekDay) día de la semana resultante
             */
            [[nodiscard]] WeekDay weekDay() const;

            /*!
             * Retorna a si misma como string legible y printer friendly 'yyyy-mm-dd'.
             * @return (std::string)
             */
            [[nodiscard]] std::string isoFormat() const;

        private:
            int _day;
            int _month;
            long _year;
            bool _validate(int d, int m, long y);
            /*!
            * Setter: setea la fecha a partir de su representación Excel
            * @param excelSerial
            */
            void _setDateFromExcelSerial(long excelSerial);

        };

        std::ostream &operator<<(std::ostream &ostr, const Date& date);


    }
}

#endif //QCODE_DATE_H
