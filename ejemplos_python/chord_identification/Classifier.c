#include "Classifier.h"

/**
* Predict class for features vector
*/
int predict(float *x) {
    uint8_t votes[6] = { 0 };
    // tree #1
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[0] <= 0.574999988079071) {
                votes[1] += 1;
            }

            else {
                if (x[7] <= 0.11500000394880772) {
                    votes[0] += 1;
                }

                else {
                    votes[1] += 1;
                }
            }
        }

        else {
            if (x[0] <= 0.03500000014901161) {
                votes[3] += 1;
            }

            else {
                if (x[9] <= 0.024999999441206455) {
                    votes[0] += 1;
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        votes[2] += 1;
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }
        }
    }

    else {
        if (x[6] <= 0.04499999899417162) {
            if (x[0] <= 0.1699999962002039) {
                if (x[7] <= 0.014999999664723873) {
                    votes[4] += 1;
                }

                else {
                    votes[5] += 1;
                }
            }

            else {
                votes[0] += 1;
            }
        }

        else {
            if (x[7] <= 0.08499999716877937) {
                votes[4] += 1;
            }

            else {
                votes[5] += 1;
            }
        }
    }

    // tree #2
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[2] <= 0.029999999329447746) {
                votes[1] += 1;
            }

            else {
                if (x[6] <= 0.024999999441206455) {
                    votes[1] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }

        else {
            if (x[8] <= 0.12499999813735485) {
                if (x[11] <= 0.054999999701976776) {
                    votes[2] += 1;
                }

                else {
                    if (x[9] <= 0.049999999813735485) {
                        if (x[4] <= 0.1249999962747097) {
                            if (x[9] <= 0.019999999552965164) {
                                votes[0] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        else {
                            votes[0] += 1;
                        }
                    }

                    else {
                        votes[2] += 1;
                    }
                }
            }

            else {
                votes[3] += 1;
            }
        }
    }

    else {
        if (x[7] <= 0.03499999921768904) {
            if (x[9] <= 0.06499999947845936) {
                votes[5] += 1;
            }

            else {
                votes[4] += 1;
            }
        }

        else {
            if (x[6] <= 0.14499999955296516) {
                if (x[0] <= 0.1699999962002039) {
                    votes[5] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }

            else {
                votes[4] += 1;
            }
        }
    }

    // tree #3
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[1] <= 0.054999999701976776) {
                votes[1] += 1;
            }

            else {
                if (x[1] <= 0.12000000104308128) {
                    votes[0] += 1;
                }

                else {
                    votes[1] += 1;
                }
            }
        }

        else {
            if (x[8] <= 0.12499999813735485) {
                if (x[9] <= 0.024999999441206455) {
                    votes[0] += 1;
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        votes[2] += 1;
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }

            else {
                votes[3] += 1;
            }
        }
    }

    else {
        if (x[7] <= 0.03499999921768904) {
            if (x[6] <= 0.009999999776482582) {
                votes[5] += 1;
            }

            else {
                votes[4] += 1;
            }
        }

        else {
            if (x[6] <= 0.14499999955296516) {
                if (x[4] <= 0.18000000156462193) {
                    votes[5] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }

            else {
                votes[4] += 1;
            }
        }
    }

    // tree #4
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[0] <= 0.574999988079071) {
                votes[1] += 1;
            }

            else {
                if (x[1] <= 0.03500000014901161) {
                    votes[1] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }

        else {
            if (x[0] <= 0.03500000014901161) {
                votes[3] += 1;
            }

            else {
                if (x[9] <= 0.024999999441206455) {
                    votes[0] += 1;
                }

                else {
                    if (x[1] <= 0.06000000052154064) {
                        if (x[3] <= 0.044999999925494194) {
                            votes[2] += 1;
                        }

                        else {
                            votes[0] += 1;
                        }
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }
        }
    }

    else {
        if (x[6] <= 0.04499999899417162) {
            if (x[4] <= 0.18000000156462193) {
                if (x[7] <= 0.014999999664723873) {
                    votes[4] += 1;
                }

                else {
                    votes[5] += 1;
                }
            }

            else {
                votes[0] += 1;
            }
        }

        else {
            if (x[7] <= 0.08499999716877937) {
                votes[4] += 1;
            }

            else {
                votes[5] += 1;
            }
        }
    }

    // tree #5
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[5] <= 0.029999999329447746) {
                if (x[6] <= 0.019999999552965164) {
                    votes[1] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }

            else {
                votes[1] += 1;
            }
        }

        else {
            if (x[8] <= 0.12499999813735485) {
                if (x[11] <= 0.054999999701976776) {
                    votes[2] += 1;
                }

                else {
                    if (x[5] <= 0.014999999664723873) {
                        votes[0] += 1;
                    }

                    else {
                        if (x[1] <= 0.024999999441206455) {
                            votes[2] += 1;
                        }

                        else {
                            votes[0] += 1;
                        }
                    }
                }
            }

            else {
                votes[3] += 1;
            }
        }
    }

    else {
        if (x[6] <= 0.04499999899417162) {
            if (x[7] <= 0.014999999664723873) {
                votes[4] += 1;
            }

            else {
                if (x[4] <= 0.18000000156462193) {
                    votes[5] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }

        else {
            if (x[11] <= 0.024999999441206455) {
                votes[4] += 1;
            }

            else {
                if (x[7] <= 0.07999999728053808) {
                    votes[4] += 1;
                }

                else {
                    votes[5] += 1;
                }
            }
        }
    }

    // tree #6
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[0] <= 0.574999988079071) {
                votes[1] += 1;
            }

            else {
                if (x[2] <= 0.019999999552965164) {
                    votes[1] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }

        else {
            if (x[8] <= 0.12499999813735485) {
                if (x[9] <= 0.024999999441206455) {
                    votes[0] += 1;
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        votes[2] += 1;
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }

            else {
                votes[3] += 1;
            }
        }
    }

    else {
        if (x[6] <= 0.04499999899417162) {
            if (x[4] <= 0.18000000156462193) {
                if (x[1] <= 0.1550000011920929) {
                    votes[5] += 1;
                }

                else {
                    votes[4] += 1;
                }
            }

            else {
                votes[0] += 1;
            }
        }

        else {
            if (x[1] <= 0.11500000208616257) {
                votes[4] += 1;
            }

            else {
                votes[5] += 1;
            }
        }
    }

    // tree #7
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[0] <= 0.574999988079071) {
                votes[1] += 1;
            }

            else {
                if (x[8] <= 0.014999999664723873) {
                    votes[1] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }

        else {
            if (x[8] <= 0.12499999813735485) {
                if (x[9] <= 0.024999999441206455) {
                    votes[0] += 1;
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        votes[2] += 1;
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }

            else {
                votes[3] += 1;
            }
        }
    }

    else {
        if (x[6] <= 0.04499999899417162) {
            if (x[7] <= 0.014999999664723873) {
                votes[4] += 1;
            }

            else {
                if (x[0] <= 0.1699999962002039) {
                    votes[5] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }

        else {
            if (x[7] <= 0.08499999716877937) {
                votes[4] += 1;
            }

            else {
                votes[5] += 1;
            }
        }
    }

    // tree #8
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[8] <= 0.024999999441206455) {
                votes[1] += 1;
            }

            else {
                if (x[9] <= 0.0400000000372529) {
                    votes[0] += 1;
                }

                else {
                    votes[1] += 1;
                }
            }
        }

        else {
            if (x[8] <= 0.12499999813735485) {
                if (x[9] <= 0.024999999441206455) {
                    votes[0] += 1;
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        votes[2] += 1;
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }

            else {
                votes[3] += 1;
            }
        }
    }

    else {
        if (x[6] <= 0.04499999899417162) {
            if (x[0] <= 0.1699999962002039) {
                if (x[1] <= 0.1550000011920929) {
                    votes[5] += 1;
                }

                else {
                    votes[4] += 1;
                }
            }

            else {
                votes[0] += 1;
            }
        }

        else {
            if (x[1] <= 0.11500000208616257) {
                votes[4] += 1;
            }

            else {
                votes[5] += 1;
            }
        }
    }

    // tree #9
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[0] <= 0.574999988079071) {
                votes[1] += 1;
            }

            else {
                if (x[10] <= 0.019999999552965164) {
                    votes[1] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }

        else {
            if (x[0] <= 0.03500000014901161) {
                votes[3] += 1;
            }

            else {
                if (x[9] <= 0.024999999441206455) {
                    votes[0] += 1;
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        votes[2] += 1;
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }
        }
    }

    else {
        if (x[6] <= 0.04499999899417162) {
            if (x[1] <= 0.1550000011920929) {
                if (x[0] <= 0.1699999962002039) {
                    votes[5] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }

            else {
                votes[4] += 1;
            }
        }

        else {
            if (x[1] <= 0.11500000208616257) {
                votes[4] += 1;
            }

            else {
                votes[5] += 1;
            }
        }
    }

    // tree #10
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[2] <= 0.029999999329447746) {
                votes[1] += 1;
            }

            else {
                if (x[3] <= 0.0400000000372529) {
                    votes[0] += 1;
                }

                else {
                    votes[1] += 1;
                }
            }
        }

        else {
            if (x[8] <= 0.12499999813735485) {
                if (x[11] <= 0.054999999701976776) {
                    votes[2] += 1;
                }

                else {
                    if (x[9] <= 0.049999999813735485) {
                        if (x[4] <= 0.1249999962747097) {
                            if (x[0] <= 0.5999999940395355) {
                                votes[2] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[0] += 1;
                        }
                    }

                    else {
                        votes[2] += 1;
                    }
                }
            }

            else {
                votes[3] += 1;
            }
        }
    }

    else {
        if (x[7] <= 0.03499999921768904) {
            if (x[6] <= 0.009999999776482582) {
                votes[5] += 1;
            }

            else {
                votes[4] += 1;
            }
        }

        else {
            if (x[0] <= 0.1699999962002039) {
                if (x[6] <= 0.14499999955296516) {
                    votes[5] += 1;
                }

                else {
                    votes[4] += 1;
                }
            }

            else {
                votes[0] += 1;
            }
        }
    }

    // tree #11
    if (x[2] <= 0.08999999985098839) {
        if (x[5] <= 0.07499999925494194) {
            if (x[0] <= 0.03500000014901161) {
                votes[3] += 1;
            }

            else {
                if (x[9] <= 0.024999999441206455) {
                    if (x[7] <= 0.17000000178813934) {
                        votes[0] += 1;
                    }

                    else {
                        votes[1] += 1;
                    }
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        if (x[4] <= 0.049999999813735485) {
                            votes[0] += 1;
                        }

                        else {
                            votes[2] += 1;
                        }
                    }

                    else {
                        if (x[11] <= 0.05500000063329935) {
                            votes[1] += 1;
                        }

                        else {
                            votes[0] += 1;
                        }
                    }
                }
            }
        }

        else {
            if (x[7] <= 0.024999999441206455) {
                votes[3] += 1;
            }

            else {
                votes[1] += 1;
            }
        }
    }

    else {
        if (x[6] <= 0.04499999899417162) {
            if (x[1] <= 0.1550000011920929) {
                if (x[0] <= 0.1699999962002039) {
                    votes[5] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }

            else {
                votes[4] += 1;
            }
        }

        else {
            if (x[7] <= 0.08499999716877937) {
                votes[4] += 1;
            }

            else {
                votes[5] += 1;
            }
        }
    }

    // tree #12
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[0] <= 0.574999988079071) {
                votes[1] += 1;
            }

            else {
                if (x[9] <= 0.019999999552965164) {
                    votes[1] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }

        else {
            if (x[0] <= 0.03500000014901161) {
                votes[3] += 1;
            }

            else {
                if (x[9] <= 0.024999999441206455) {
                    votes[0] += 1;
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        votes[2] += 1;
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }
        }
    }

    else {
        if (x[6] <= 0.04499999899417162) {
            if (x[0] <= 0.1699999962002039) {
                if (x[1] <= 0.1550000011920929) {
                    votes[5] += 1;
                }

                else {
                    votes[4] += 1;
                }
            }

            else {
                votes[0] += 1;
            }
        }

        else {
            if (x[7] <= 0.08499999716877937) {
                votes[4] += 1;
            }

            else {
                votes[5] += 1;
            }
        }
    }

    // tree #13
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[8] <= 0.024999999441206455) {
                votes[1] += 1;
            }

            else {
                if (x[0] <= 0.5049999952316284) {
                    votes[1] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }

        else {
            if (x[0] <= 0.03500000014901161) {
                votes[3] += 1;
            }

            else {
                if (x[9] <= 0.024999999441206455) {
                    votes[0] += 1;
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        votes[2] += 1;
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }
        }
    }

    else {
        if (x[7] <= 0.03499999921768904) {
            if (x[6] <= 0.009999999776482582) {
                votes[5] += 1;
            }

            else {
                votes[4] += 1;
            }
        }

        else {
            if (x[0] <= 0.1699999962002039) {
                if (x[6] <= 0.14499999955296516) {
                    votes[5] += 1;
                }

                else {
                    votes[4] += 1;
                }
            }

            else {
                votes[0] += 1;
            }
        }
    }

    // tree #14
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[0] <= 0.574999988079071) {
                votes[1] += 1;
            }

            else {
                if (x[9] <= 0.019999999552965164) {
                    votes[1] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }

        else {
            if (x[0] <= 0.03500000014901161) {
                votes[3] += 1;
            }

            else {
                if (x[9] <= 0.024999999441206455) {
                    votes[0] += 1;
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        votes[2] += 1;
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }
        }
    }

    else {
        if (x[6] <= 0.04499999899417162) {
            if (x[7] <= 0.014999999664723873) {
                votes[4] += 1;
            }

            else {
                if (x[0] <= 0.1699999962002039) {
                    votes[5] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }

        else {
            if (x[7] <= 0.08499999716877937) {
                votes[4] += 1;
            }

            else {
                votes[5] += 1;
            }
        }
    }

    // tree #15
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[0] <= 0.574999988079071) {
                votes[1] += 1;
            }

            else {
                if (x[0] <= 0.6649999916553497) {
                    votes[0] += 1;
                }

                else {
                    votes[1] += 1;
                }
            }
        }

        else {
            if (x[0] <= 0.03500000014901161) {
                votes[3] += 1;
            }

            else {
                if (x[9] <= 0.024999999441206455) {
                    votes[0] += 1;
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        votes[2] += 1;
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }
        }
    }

    else {
        if (x[6] <= 0.04499999899417162) {
            if (x[7] <= 0.014999999664723873) {
                votes[4] += 1;
            }

            else {
                if (x[0] <= 0.1699999962002039) {
                    votes[5] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }

        else {
            if (x[1] <= 0.11500000208616257) {
                votes[4] += 1;
            }

            else {
                votes[5] += 1;
            }
        }
    }

    // tree #16
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[5] <= 0.029999999329447746) {
                if (x[1] <= 0.0400000000372529) {
                    votes[1] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }

            else {
                votes[1] += 1;
            }
        }

        else {
            if (x[8] <= 0.12499999813735485) {
                if (x[9] <= 0.024999999441206455) {
                    votes[0] += 1;
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        votes[2] += 1;
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }

            else {
                votes[3] += 1;
            }
        }
    }

    else {
        if (x[6] <= 0.04499999899417162) {
            if (x[4] <= 0.18000000156462193) {
                if (x[7] <= 0.014999999664723873) {
                    votes[4] += 1;
                }

                else {
                    votes[5] += 1;
                }
            }

            else {
                votes[0] += 1;
            }
        }

        else {
            if (x[7] <= 0.08499999716877937) {
                votes[4] += 1;
            }

            else {
                votes[5] += 1;
            }
        }
    }

    // tree #17
    if (x[0] <= 0.1099999975413084) {
        if (x[7] <= 0.03499999921768904) {
            if (x[9] <= 0.06499999947845936) {
                if (x[11] <= 0.04999999888241291) {
                    votes[5] += 1;
                }

                else {
                    votes[3] += 1;
                }
            }

            else {
                votes[4] += 1;
            }
        }

        else {
            if (x[10] <= 0.05999999865889549) {
                if (x[6] <= 0.14499999955296516) {
                    votes[5] += 1;
                }

                else {
                    votes[4] += 1;
                }
            }

            else {
                votes[2] += 1;
            }
        }
    }

    else {
        if (x[4] <= 0.06999999843537807) {
            if (x[8] <= 0.024999999441206455) {
                votes[1] += 1;
            }

            else {
                if (x[7] <= 0.07500000111758709) {
                    votes[0] += 1;
                }

                else {
                    votes[1] += 1;
                }
            }
        }

        else {
            if (x[9] <= 0.024999999441206455) {
                votes[0] += 1;
            }

            else {
                if (x[7] <= 0.08000000193715096) {
                    votes[2] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }
    }

    // tree #18
    if (x[0] <= 0.1099999975413084) {
        if (x[6] <= 0.024999999441206455) {
            if (x[1] <= 0.1550000011920929) {
                votes[5] += 1;
            }

            else {
                votes[4] += 1;
            }
        }

        else {
            if (x[8] <= 0.12999999895691872) {
                if (x[7] <= 0.04999999888241291) {
                    votes[4] += 1;
                }

                else {
                    if (x[4] <= 0.06000000052154064) {
                        votes[5] += 1;
                    }

                    else {
                        votes[2] += 1;
                    }
                }
            }

            else {
                votes[3] += 1;
            }
        }
    }

    else {
        if (x[4] <= 0.06999999843537807) {
            if (x[0] <= 0.574999988079071) {
                votes[1] += 1;
            }

            else {
                if (x[10] <= 0.019999999552965164) {
                    votes[1] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }
        }

        else {
            if (x[11] <= 0.054999999701976776) {
                votes[2] += 1;
            }

            else {
                if (x[5] <= 0.014999999664723873) {
                    votes[0] += 1;
                }

                else {
                    if (x[1] <= 0.024999999441206455) {
                        votes[2] += 1;
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }
        }
    }

    // tree #19
    if (x[2] <= 0.08999999985098839) {
        if (x[4] <= 0.06499999947845936) {
            if (x[5] <= 0.029999999329447746) {
                if (x[6] <= 0.019999999552965164) {
                    votes[1] += 1;
                }

                else {
                    votes[0] += 1;
                }
            }

            else {
                votes[1] += 1;
            }
        }

        else {
            if (x[0] <= 0.03500000014901161) {
                votes[3] += 1;
            }

            else {
                if (x[9] <= 0.024999999441206455) {
                    votes[0] += 1;
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        votes[2] += 1;
                    }

                    else {
                        votes[0] += 1;
                    }
                }
            }
        }
    }

    else {
        if (x[7] <= 0.03499999921768904) {
            if (x[2] <= 0.7849999964237213) {
                votes[4] += 1;
            }

            else {
                votes[5] += 1;
            }
        }

        else {
            if (x[4] <= 0.18000000156462193) {
                if (x[6] <= 0.14499999955296516) {
                    votes[5] += 1;
                }

                else {
                    votes[4] += 1;
                }
            }

            else {
                votes[0] += 1;
            }
        }
    }

    // tree #20
    if (x[2] <= 0.08999999985098839) {
        if (x[5] <= 0.07499999925494194) {
            if (x[8] <= 0.12499999813735485) {
                if (x[9] <= 0.024999999441206455) {
                    if (x[0] <= 0.699999988079071) {
                        votes[0] += 1;
                    }

                    else {
                        votes[1] += 1;
                    }
                }

                else {
                    if (x[7] <= 0.08000000193715096) {
                        if (x[4] <= 0.049999999813735485) {
                            votes[0] += 1;
                        }

                        else {
                            votes[2] += 1;
                        }
                    }

                    else {
                        if (x[11] <= 0.05500000063329935) {
                            votes[1] += 1;
                        }

                        else {
                            votes[0] += 1;
                        }
                    }
                }
            }

            else {
                votes[3] += 1;
            }
        }

        else {
            if (x[4] <= 0.18000000528991222) {
                votes[1] += 1;
            }

            else {
                votes[3] += 1;
            }
        }
    }

    else {
        if (x[7] <= 0.03499999921768904) {
            if (x[2] <= 0.7849999964237213) {
                votes[4] += 1;
            }

            else {
                votes[5] += 1;
            }
        }

        else {
            if (x[4] <= 0.18000000156462193) {
                if (x[6] <= 0.14499999955296516) {
                    votes[5] += 1;
                }

                else {
                    votes[4] += 1;
                }
            }

            else {
                votes[0] += 1;
            }
        }
    }

    // return argmax of votes
    uint8_t classIdx = 0;
    float maxVotes = votes[0];

    for (uint8_t i = 1; i < 6; i++) {
        if (votes[i] > maxVotes) {
            classIdx = i;
            maxVotes = votes[i];
        }
    }

    return classIdx;
};
/**
* Predict readable class name
*/
const char* predictLabel(float *x) {
    return idxToLabel(predict(x));
};
/**
* Convert class idx to readable name
*/
const char* idxToLabel(uint8_t classIdx) {
    switch (classIdx) {
        case 0:
        return "DO";
        case 1:
        return "FA";
        case 2:
        return "LAm";
        case 3:
        return "MI";
        case 4:
        return "RE";
        case 5:
        return "SOL";
        default:
        return "Houston we have a problem";
    }
};