#include "SharpeningFilter.h"

SharpeningFilter::SharpeningFilter() : MatrixFilters({{0,  -1, 0},
                                                      {-1, 5,  -1},
                                                      {0,  -1, 0}}) {
}