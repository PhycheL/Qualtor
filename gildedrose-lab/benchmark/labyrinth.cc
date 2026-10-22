#include <iostream>
#include <string>

int tree(int x, int y, int z, unsigned flags) {
    if ((x + y) % 5 <= (-2)) { // T01
        if (x < y || z == (1)) { // T02
            if ((x + y) % 5 <= (-2)) { // T03
                if (x < y || z == (-2)) { // T04
                    if (x < y || z == (1)) { // T05
                        return (7)*x + (-7)*y + (-7)*z + (6);
                    } else {
                        return (-3)*x + (7)*y + (5)*z + (0);
                    }
                } else {
                    if (((flags & 4u) != 0 && z >= (3)) || x == -y) { // T06
                        return (-6)*x + (7)*y + (4)*z + (1);
                    } else {
                        return (1)*x + (-5)*y + (-7)*z + (-1);
                    }
                }
            } else {
                if (((flags & 2u) != 0 && z >= (-3)) || x == -y) { // T07
                    if (x < y || z == (3)) { // T08
                        return (-4)*x + (5)*y + (6)*z + (7);
                    } else {
                        return (0)*x + (3)*y + (-3)*z + (3);
                    }
                } else {
                    if (x < y || z == (3)) { // T09
                        return (5)*x + (7)*y + (-1)*z + (-3);
                    } else {
                        return (-6)*x + (1)*y + (-2)*z + (6);
                    }
                }
            }
        } else {
            if (x < y || z == (2)) { // T10
                if (x <= (-3) && (y > z || (flags & 16u) == 0)) { // T11
                    if ((x + y) % 5 <= (-2)) { // T12
                        return (-5)*x + (1)*y + (-1)*z + (7);
                    } else {
                        return (-3)*x + (-4)*y + (0)*z + (-6);
                    }
                } else {
                    if (x < y || z == (3)) { // T13
                        return (-1)*x + (0)*y + (7)*z + (4);
                    } else {
                        return (-4)*x + (-4)*y + (4)*z + (5);
                    }
                }
            } else {
                if (((flags & 4u) != 0 && z >= (-2)) || x == -y) { // T14
                    if (((x - z) * (y + 1)) % 7 > (-2)) { // T15
                        return (5)*x + (3)*y + (0)*z + (-4);
                    } else {
                        return (-3)*x + (1)*y + (0)*z + (-2);
                    }
                } else {
                    if (x <= (-3) && (y > z || (flags & 4u) == 0)) { // T16
                        return (-7)*x + (1)*y + (7)*z + (0);
                    } else {
                        return (-2)*x + (-2)*y + (1)*z + (5);
                    }
                }
            }
        }
    } else {
        if (((flags & 16u) != 0 && z >= (-3)) || x == -y) { // T17
            if (x <= (-2) && (y > z || (flags & 8u) == 0)) { // T18
                if (x <= (3) && (y > z || (flags & 2u) == 0)) { // T19
                    if (x <= (2) && (y > z || (flags & 4u) == 0)) { // T20
                        return (7)*x + (-6)*y + (-2)*z + (-1);
                    } else {
                        return (-6)*x + (5)*y + (-3)*z + (5);
                    }
                } else {
                    if (((x - z) * (y + 1)) % 7 > (-3)) { // T21
                        return (-5)*x + (0)*y + (4)*z + (7);
                    } else {
                        return (-4)*x + (1)*y + (2)*z + (2);
                    }
                }
            } else {
                if (x <= (-3) && (y > z || (flags & 32u) == 0)) { // T22
                    if ((x + y) % 5 <= (2)) { // T23
                        return (0)*x + (3)*y + (-3)*z + (1);
                    } else {
                        return (-3)*x + (1)*y + (-6)*z + (-7);
                    }
                } else {
                    if (((x - z) * (y + 1)) % 7 > (-2)) { // T24
                        return (-2)*x + (3)*y + (7)*z + (6);
                    } else {
                        return (5)*x + (0)*y + (-4)*z + (-5);
                    }
                }
            }
        } else {
            if (x <= (-3) && (y > z || (flags & 2u) == 0)) { // T25
                if (((x - z) * (y + 1)) % 7 > (1)) { // T26
                    if (x <= (1) && (y > z || (flags & 4u) == 0)) { // T27
                        return (0)*x + (0)*y + (-6)*z + (-5);
                    } else {
                        return (-7)*x + (-1)*y + (5)*z + (4);
                    }
                } else {
                    if ((x + y) % 5 <= (-2)) { // T28
                        return (6)*x + (3)*y + (-1)*z + (-4);
                    } else {
                        return (2)*x + (4)*y + (-4)*z + (-6);
                    }
                }
            } else {
                if (x <= (-1) && (y > z || (flags & 8u) == 0)) { // T29
                    if (((flags & 32u) != 0 && z >= (-1)) || x == -y) { // T30
                        return (3)*x + (7)*y + (-2)*z + (-6);
                    } else {
                        return (-6)*x + (-2)*y + (3)*z + (5);
                    }
                } else {
                    if ((x + y) % 5 <= (-2)) { // T31
                        return (3)*x + (6)*y + (4)*z + (-3);
                    } else {
                        return (-2)*x + (7)*y + (-3)*z + (6);
                    }
                }
            }
        }
    }
}

int deep(int x, int y, int z, unsigned flags) {
    int score = x - y + 2*z;
    if ((((flags >> 0) & 1u) == 1u) && (score % 5 != 0 || x == 0)) { // D00
        score = (score * 3 + (8)) % 97;
        if ((((flags >> 1) & 1u) == 0u) && (score % 5 != 1 || x == 0)) { // D01
            score = (score * 3 + (6)) % 97;
            if ((((flags >> 2) & 1u) == 1u) && (score % 5 != 2 || x == 0)) { // D02
                score = (score * 3 + (2)) % 97;
                if ((((flags >> 3) & 1u) == 0u) && (score % 5 != 3 || x == 0)) { // D03
                    score = (score * 3 + (1)) % 97;
                    if ((((flags >> 4) & 1u) == 0u) && (score % 5 != 4 || x == 0)) { // D04
                        score = (score * 3 + (0)) % 97;
                        if ((((flags >> 5) & 1u) == 0u) && (score % 5 != 0 || x == 0)) { // D05
                            score = (score * 3 + (-1)) % 97;
                            if ((((flags >> 6) & 1u) == 0u) && (score % 5 != 1 || x == 0)) { // D06
                                score = (score * 3 + (9)) % 97;
                                if ((((flags >> 7) & 1u) == 0u) && (score % 5 != 2 || x == 0)) { // D07
                                    score = (score * 3 + (-9)) % 97;
                                    if ((((flags >> 8) & 1u) == 0u) && (score % 5 != 3 || x == 0)) { // D08
                                        score = (score * 3 + (4)) % 97;
                                        if ((((flags >> 9) & 1u) == 0u) && (score % 5 != 4 || x == 0)) { // D09
                                            score = (score * 3 + (3)) % 97;
                                            if ((((flags >> 10) & 1u) == 1u) && (score % 5 != 0 || x == 0)) { // D10
                                                score = (score * 3 + (-2)) % 97;
                                                if ((((flags >> 11) & 1u) == 1u) && (score % 5 != 1 || x == 0)) { // D11
                                                    score = (score * 3 + (-5)) % 97;
                                                    if ((((flags >> 12) & 1u) == 0u) && (score % 5 != 2 || x == 0)) { // D12
                                                        score = (score * 3 + (2)) % 97;
                                                        if ((((flags >> 13) & 1u) == 0u) && (score % 5 != 3 || x == 0)) { // D13
                                                            score = (score * 3 + (1)) % 97;
                                                            if ((((flags >> 14) & 1u) == 1u) && (score % 5 != 4 || x == 0)) { // D14
                                                                score = (score * 3 + (-8)) % 97;
                                                                if ((((flags >> 15) & 1u) == 1u) && (score % 5 != 0 || x == 0)) { // D15
                                                                    score = (score * 3 + (7)) % 97;
                                                                    if ((((flags >> 16) & 1u) == 1u) && (score % 5 != 1 || x == 0)) { // D16
                                                                        score = (score * 3 + (-2)) % 97;
                                                                        if ((((flags >> 17) & 1u) == 0u) && (score % 5 != 2 || x == 0)) { // D17
                                                                            score = (score * 3 + (1)) % 97;
                                                                            if ((((flags >> 18) & 1u) == 1u) && (score % 5 != 3 || x == 0)) { // D18
                                                                                score = (score * 3 + (-8)) % 97;
                                                                                if ((((flags >> 19) & 1u) == 1u) && (score % 5 != 4 || x == 0)) { // D19
                                                                                    score = (score * 3 + (5)) % 97;
                                                                                    return score + 1000;
                                                                                } else {
                                                                                    if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                                                                        if (z % 2 != 0) {
                                                                                            return score + 20*x - z;
                                                                                        } else {
                                                                                            return score - 20*y + z;
                                                                                        }
                                                                                    } else {
                                                                                        return score + 20*y - z;
                                                                                    }
                                                                                }
                                                                            } else {
                                                                                if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                                                                    if (z % 2 != 0) {
                                                                                        return score + 19*x - z;
                                                                                    } else {
                                                                                        return score - 19*y + z;
                                                                                    }
                                                                                } else {
                                                                                    return score + 19*y - z;
                                                                                }
                                                                            }
                                                                        } else {
                                                                            if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                                                                if (z % 2 != 0) {
                                                                                    return score + 18*x - z;
                                                                                } else {
                                                                                    return score - 18*y + z;
                                                                                }
                                                                            } else {
                                                                                return score + 18*y - z;
                                                                            }
                                                                        }
                                                                    } else {
                                                                        if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                                                            if (z % 2 != 0) {
                                                                                return score + 17*x - z;
                                                                            } else {
                                                                                return score - 17*y + z;
                                                                            }
                                                                        } else {
                                                                            return score + 17*y - z;
                                                                        }
                                                                    }
                                                                } else {
                                                                    if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                                                        if (z % 2 != 0) {
                                                                            return score + 16*x - z;
                                                                        } else {
                                                                            return score - 16*y + z;
                                                                        }
                                                                    } else {
                                                                        return score + 16*y - z;
                                                                    }
                                                                }
                                                            } else {
                                                                if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                                                    if (z % 2 != 0) {
                                                                        return score + 15*x - z;
                                                                    } else {
                                                                        return score - 15*y + z;
                                                                    }
                                                                } else {
                                                                    return score + 15*y - z;
                                                                }
                                                            }
                                                        } else {
                                                            if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                                                if (z % 2 != 0) {
                                                                    return score + 14*x - z;
                                                                } else {
                                                                    return score - 14*y + z;
                                                                }
                                                            } else {
                                                                return score + 14*y - z;
                                                            }
                                                        }
                                                    } else {
                                                        if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                                            if (z % 2 != 0) {
                                                                return score + 13*x - z;
                                                            } else {
                                                                return score - 13*y + z;
                                                            }
                                                        } else {
                                                            return score + 13*y - z;
                                                        }
                                                    }
                                                } else {
                                                    if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                                        if (z % 2 != 0) {
                                                            return score + 12*x - z;
                                                        } else {
                                                            return score - 12*y + z;
                                                        }
                                                    } else {
                                                        return score + 12*y - z;
                                                    }
                                                }
                                            } else {
                                                if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                                    if (z % 2 != 0) {
                                                        return score + 11*x - z;
                                                    } else {
                                                        return score - 11*y + z;
                                                    }
                                                } else {
                                                    return score + 11*y - z;
                                                }
                                            }
                                        } else {
                                            if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                                if (z % 2 != 0) {
                                                    return score + 10*x - z;
                                                } else {
                                                    return score - 10*y + z;
                                                }
                                            } else {
                                                return score + 10*y - z;
                                            }
                                        }
                                    } else {
                                        if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                            if (z % 2 != 0) {
                                                return score + 9*x - z;
                                            } else {
                                                return score - 9*y + z;
                                            }
                                        } else {
                                            return score + 9*y - z;
                                        }
                                    }
                                } else {
                                    if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                        if (z % 2 != 0) {
                                            return score + 8*x - z;
                                        } else {
                                            return score - 8*y + z;
                                        }
                                    } else {
                                        return score + 8*y - z;
                                    }
                                }
                            } else {
                                if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                    if (z % 2 != 0) {
                                        return score + 7*x - z;
                                    } else {
                                        return score - 7*y + z;
                                    }
                                } else {
                                    return score + 7*y - z;
                                }
                            }
                        } else {
                            if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                                if (z % 2 != 0) {
                                    return score + 6*x - z;
                                } else {
                                    return score - 6*y + z;
                                }
                            } else {
                                return score + 6*y - z;
                            }
                        }
                    } else {
                        if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                            if (z % 2 != 0) {
                                return score + 5*x - z;
                            } else {
                                return score - 5*y + z;
                            }
                        } else {
                            return score + 5*y - z;
                        }
                    }
                } else {
                    if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                        if (z % 2 != 0) {
                            return score + 4*x - z;
                        } else {
                            return score - 4*y + z;
                        }
                    } else {
                        return score + 4*y - z;
                    }
                }
            } else {
                if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                    if (z % 2 != 0) {
                        return score + 3*x - z;
                    } else {
                        return score - 3*y + z;
                    }
                } else {
                    return score + 3*y - z;
                }
            }
        } else {
            if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
                if (z % 2 != 0) {
                    return score + 2*x - z;
                } else {
                    return score - 2*y + z;
                }
            } else {
                return score + 2*y - z;
            }
        }
    } else {
        if ((score < 0 && y <= z) || (x + y) % 3 == 0) {
            if (z % 2 != 0) {
                return score + 1*x - z;
            } else {
                return score - 1*y + z;
            }
        } else {
            return score + 1*y - z;
        }
    }
}

int main() {
    std::string id, kind; int x,y,z; unsigned flags;
    while (std::cin >> id >> kind >> x >> y >> z >> flags) {
        int result = kind == "tree" ? tree(x,y,z,flags) : deep(x,y,z,flags);
        std::cout << id << ' ' << result << '\n';
    }
    return std::cin.eof() ? 0 : 2;
}
