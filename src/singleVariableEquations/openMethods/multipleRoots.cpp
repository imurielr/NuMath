#include <stdio.h>

#include <cmath>
#include <cstring>
#include "multipleRoots.h"

#include "../../../lib/exceptions.h"

namespace numath {
    namespace singleVariableEquations {

        double multipleRoots(double (*func)(double), double (*dFunc)(double), double (*d2Func)(double), double x0, int nIter, double tol, const char *errorType, std::vector<std::vector<double>> &table) {
            
            int count;
            double fx, dfx, d2fx;
            double x1, x1_denominator;
            double error;

            fx = func(x0);
            dfx = dFunc(x0);
            d2fx = d2Func(x0);
            x1_denominator = pow(dfx, 2) - fx * d2fx;
            error = tol + 1;
            count = 0;

            // Add info to the table
            std::vector<double> iterVector1 = {(double) count, x0, fx, error};
            table.push_back(iterVector1);
            // ---------------------

            while (error > tol && fx != 0 && x1_denominator != 0 && count < nIter) {
                x1 = x0 - ((fx * dfx) / x1_denominator);
                fx = func(x1);
                dfx = dFunc(x1);
                d2fx = d2Func(x1);
                error = ((strcmp(errorType, "abs") == 0) ? fabs(x1 - x0) : fabs((x1 - x0) / x1));
                x1_denominator = pow(dfx, 2) - fx * d2fx;
                count++;
                x0 = x1;

                // Add info to the table
                std::vector<double> iterVector2 = {(double) count, x0, fx, error};
                table.push_back(iterVector2);
                // ---------------------
            }

            if (fx == 0) {
                // x0 is a root
                return x0;
            }
            else if (error < tol) {
                // x0 (and x1 has the same value) is an approx of the root
                return x1;
            }
            else if (x1_denominator == 0) {
                throw DenominatorException();
            }
            else {
                throw IterException();
            }

        }

    }
}