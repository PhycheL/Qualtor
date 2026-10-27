// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_02.h"

#include <gtest/gtest.h>

#include <cmath>
#include <map>
#include <string>
#include <vector>

namespace {

template <class T>
void ExpectNearScalar(T actual, T expected, double tolerance) {
    EXPECT_NEAR(actual, expected, tolerance * (1 + std::fabs(static_cast<double>(expected))));
}

template <class T>
void ExpectNearVec(const std::vector<T>& actual, const std::vector<T>& expected, double tolerance) {
    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); ++i) ExpectNearScalar(actual[i], expected[i], tolerance);
}

}  // namespace

TEST(Characterization, sum_product_01) {
    EXPECT_EQ((sum_product(std::vector<int >{})), (std::vector<int >{0, 1}));
    EXPECT_EQ((sum_product(std::vector<int >{0, 1, 99999})), (std::vector<int >{100000, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{1, 2, 3, 4})), (std::vector<int >{10, 24}));
    EXPECT_EQ((sum_product(std::vector<int >{1, 544, 24, 3, 5})), (std::vector<int >{577, 195840}));
    EXPECT_EQ((sum_product(std::vector<int >{10, 7})), (std::vector<int >{17, 70}));
    EXPECT_EQ((sum_product(std::vector<int >{1, 1, 1})), (std::vector<int >{3, 1}));
    EXPECT_EQ((sum_product(std::vector<int >{0, 4})), (std::vector<int >{4, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{19, 4, 10, 21})), (std::vector<int >{54, 15960}));
    EXPECT_EQ((sum_product(std::vector<int >{10, 24, -116, 3, -10, 1, 7, -1})), (std::vector<int >{-82, -5846400}));
    EXPECT_EQ((sum_product(std::vector<int >{10, 24, -623})), (std::vector<int >{-589, -149520}));
    EXPECT_EQ((sum_product(std::vector<int >{3, 1})), (std::vector<int >{4, 3}));
    EXPECT_EQ((sum_product(std::vector<int >{0})), (std::vector<int >{0, 0}));
}

TEST(Characterization, rolling_max_01) {
    EXPECT_EQ((rolling_max(std::vector<int >{3, 100, 3, 100, 3})), (std::vector<int >{3, 100, 100, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{-8, 0, 1, -272})), (std::vector<int >{0, 0, 1, 1}));
    EXPECT_EQ((rolling_max(std::vector<int >{})), (std::vector<int >{}));
    EXPECT_EQ((rolling_max(std::vector<int >{1, 2, 3, 4, 3})), (std::vector<int >{1, 2, 3, 4, 4}));
    EXPECT_EQ((rolling_max(std::vector<int >{1, 2, 3, 3, 3, 4, 4})), (std::vector<int >{1, 2, 3, 3, 3, 4, 4}));
    EXPECT_EQ((rolling_max(std::vector<int >{3, 2, 3, 275, 3})), (std::vector<int >{3, 3, 3, 275, 275}));
    EXPECT_EQ((rolling_max(std::vector<int >{100, -10, -8, -4, 28})), (std::vector<int >{100, 100, 100, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{100, 28, 4, 4, 3})), (std::vector<int >{100, 100, 100, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{212, 28})), (std::vector<int >{212, 212}));
    EXPECT_EQ((rolling_max(std::vector<int >{2, 3, 4})), (std::vector<int >{2, 3, 4}));
    EXPECT_EQ((rolling_max(std::vector<int >{98, 28})), (std::vector<int >{98, 98}));
    EXPECT_EQ((rolling_max(std::vector<int >{4, 2, 3, 4})), (std::vector<int >{4, 4, 4, 4}));
}

TEST(Characterization, is_palindrome_01) {
    EXPECT_EQ((is_palindrome(std::string(""))), (true));
    EXPECT_EQ((is_palindrome(std::string("c"))), (true));
    EXPECT_EQ((is_palindrome(std::string("Bjerryrre3j"))), (false));
    EXPECT_EQ((is_palindrome(std::string("0x"))), (false));
    EXPECT_EQ((is_palindrome(std::string("ysy3"))), (false));
    EXPECT_EQ((is_palindrome(std::string("KfMk0OV"))), (false));
    EXPECT_EQ((is_palindrome(std::string("q"))), (true));
    EXPECT_EQ((is_palindrome(std::string("fhsBTwo8f2FZ"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xyzyx"))), (true));
    EXPECT_EQ((is_palindrome(std::string("7"))), (true));
    EXPECT_EQ((is_palindrome(std::string("cat"))), (false));
    EXPECT_EQ((is_palindrome(std::string("H ci wExwZ"))), (false));
}

TEST(Characterization, make_palindrome_01) {
    EXPECT_EQ((make_palindrome(std::string("cata"))), (std::string("catac")));
    EXPECT_EQ((make_palindrome(std::string("jerryrrej"))), (std::string("jerryrrej")));
    EXPECT_EQ((make_palindrome(std::string("xyz"))), (std::string("xyzyx")));
    EXPECT_EQ((make_palindrome(std::string("qRpWHWo"))), (std::string("qRpWHWoWHWpRq")));
    EXPECT_EQ((make_palindrome(std::string("jerruy"))), (std::string("jerruyurrej")));
    EXPECT_EQ((make_palindrome(std::string("bR2D"))), (std::string("bR2D2Rb")));
    EXPECT_EQ((make_palindrome(std::string("roKnouE"))), (std::string("roKnouEuonKor")));
    EXPECT_EQ((make_palindrome(std::string("xyzyx"))), (std::string("xyzyx")));
    EXPECT_EQ((make_palindrome(std::string(""))), (std::string("")));
    EXPECT_EQ((make_palindrome(std::string("catRc"))), (std::string("catRcRtac")));
    EXPECT_EQ((make_palindrome(std::string("x"))), (std::string("x")));
    EXPECT_EQ((make_palindrome(std::string("ca6a"))), (std::string("ca6ac")));
}

TEST(Characterization, string_xor_01) {
    EXPECT_EQ((string_xor(std::string("wylhXA Net"), std::string("HMU"))), (std::string("111")));
    EXPECT_EQ((string_xor(std::string("m0dWyKBlr"), std::string("JRj5B9C"))), (std::string("1111111")));
    EXPECT_EQ((string_xor(std::string("1"), std::string("11000"))), (std::string("0")));
    EXPECT_EQ((string_xor(std::string("111000"), std::string("xsidURcce"))), (std::string("111111")));
    EXPECT_EQ((string_xor(std::string("111000"), std::string("101010"))), (std::string("010010")));
    EXPECT_EQ((string_xor(std::string("C1"), std::string("100"))), (std::string("11")));
    EXPECT_EQ((string_xor(std::string("J8zisg4882pt"), std::string("D1W15tic"))), (std::string("11111111")));
    EXPECT_EQ((string_xor(std::string("1"), std::string(""))), (std::string("")));
    EXPECT_EQ((string_xor(std::string(""), std::string("0100"))), (std::string("")));
    EXPECT_EQ((string_xor(std::string("100"), std::string("010"))), (std::string("110")));
    EXPECT_EQ((string_xor(std::string("0000"), std::string("ftDFppRvUTHf"))), (std::string("1111")));
    EXPECT_EQ((string_xor(std::string("110"), std::string("0s1"))), (std::string("111")));
}

TEST(Characterization, longest_01) {
    EXPECT_EQ((longest(std::vector<std::string >{std::string("ccc"), std::string("bb"), std::string("ccc")})), (std::string("ccc")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("h"), std::string("n"), std::string("x")})), (std::string("h")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("J0xn412wNK"), std::string("cOouagz5RU1"), std::string("kk"), std::string("x")})), (std::string("cOouagz5RU1")));
    EXPECT_EQ((longest(std::vector<std::string >{})), (std::string("")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("b"), std::string("cvMd7 7")})), (std::string("cvMd7 7")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("www"), std::string("2Z")})), (std::string("www")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("y"), std::string("z"), std::string("kk")})), (std::string("kk")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("yyy"), std::string("zzzz"), std::string("www"), std::string("kkkk"), std::string("abc")})), (std::string("zzzz")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("MnmTDjAYG"), std::string("kkkk"), std::string("kkkk"), std::string(" Co37WWcUj"), std::string("z"), std::string("abc"), std::string("ZY9ol 9")})), (std::string(" Co37WWcUj")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string(""), std::string("zzzz"), std::string("lGNobYNFmRHN")})), (std::string("lGNobYNFmRHN")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("ccc")})), (std::string("ccc")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("y"), std::string("z")})), (std::string("x")));
}

TEST(Characterization, greatest_common_divisor_01) {
    EXPECT_EQ((greatest_common_divisor(8, -8)), (-8));
    EXPECT_EQ((greatest_common_divisor(12, 574)), (2));
    EXPECT_EQ((greatest_common_divisor(7, 16)), (1));
    EXPECT_EQ((greatest_common_divisor(1, 12)), (1));
    EXPECT_EQ((greatest_common_divisor(14, 11)), (1));
    EXPECT_EQ((greatest_common_divisor(23, 7)), (1));
    EXPECT_EQ((greatest_common_divisor(12, 85)), (1));
    EXPECT_EQ((greatest_common_divisor(25, 15)), (5));
    EXPECT_EQ((greatest_common_divisor(1, 592)), (1));
    EXPECT_EQ((greatest_common_divisor(144, 27)), (9));
    EXPECT_EQ((greatest_common_divisor(99999, 452)), (1));
    EXPECT_EQ((greatest_common_divisor(6, 4)), (2));
}

TEST(Characterization, all_prefixes_01) {
    EXPECT_EQ((all_prefixes(std::string("u"))), (std::vector<std::string >{std::string("u")}));
    EXPECT_EQ((all_prefixes(std::string("q"))), (std::vector<std::string >{std::string("q")}));
    EXPECT_EQ((all_prefixes(std::string("ab"))), (std::vector<std::string >{std::string("a"), std::string("ab")}));
    EXPECT_EQ((all_prefixes(std::string("asdfgh"))), (std::vector<std::string >{std::string("a"), std::string("as"), std::string("asd"), std::string("asdf"), std::string("asdfg"), std::string("asdfgh")}));
    EXPECT_EQ((all_prefixes(std::string("es"))), (std::vector<std::string >{std::string("e"), std::string("es")}));
    EXPECT_EQ((all_prefixes(std::string("o"))), (std::vector<std::string >{std::string("o")}));
    EXPECT_EQ((all_prefixes(std::string("la"))), (std::vector<std::string >{std::string("l"), std::string("la")}));
    EXPECT_EQ((all_prefixes(std::string("Ic3MCh0j"))), (std::vector<std::string >{std::string("I"), std::string("Ic"), std::string("Ic3"), std::string("Ic3M"), std::string("Ic3MC"), std::string("Ic3MCh"), std::string("Ic3MCh0"), std::string("Ic3MCh0j")}));
    EXPECT_EQ((all_prefixes(std::string("asdfg"))), (std::vector<std::string >{std::string("a"), std::string("as"), std::string("asd"), std::string("asdf"), std::string("asdfg")}));
    EXPECT_EQ((all_prefixes(std::string("asd"))), (std::vector<std::string >{std::string("a"), std::string("as"), std::string("asd")}));
    EXPECT_EQ((all_prefixes(std::string("asmfogh"))), (std::vector<std::string >{std::string("a"), std::string("as"), std::string("asm"), std::string("asmf"), std::string("asmfo"), std::string("asmfog"), std::string("asmfogh")}));
    EXPECT_EQ((all_prefixes(std::string("Ny1oAh9bXH"))), (std::vector<std::string >{std::string("N"), std::string("Ny"), std::string("Ny1"), std::string("Ny1o"), std::string("Ny1oA"), std::string("Ny1oAh"), std::string("Ny1oAh9"), std::string("Ny1oAh9b"), std::string("Ny1oAh9bX"), std::string("Ny1oAh9bXH")}));
}

TEST(Characterization, string_sequence_01) {
    EXPECT_EQ((string_sequence(958)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256 257 258 259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294 295 296 297 298 299 300 301 302 303 304 305 306 307 308 309 310 311 312 313 314 315 316 317 318 319 320 321 322 323 324 325 326 327 328 329 330 331 332 333 334 335 336 337 338 339 340 341 342 343 344 345 346 347 348 349 350 351 352 353 354 355 356 357 358 359 360 361 362 363 364 365 366 367 368 369 370 371 372 373 374 375 376 377 378 379 380 381 382 383 384 385 386 387 388 389 390 391 392 393 394 395 396 397 398 399 400 401 402 403 404 405 406 407 408 409 410 411 412 413 414 415 416 417 418 419 420 421 422 423 424 425 426 427 428 429 430 431 432 433 434 435 436 437 438 439 440 441 442 443 444 445 446 447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465 466 467 468 469 470 471 472 473 474 475 476 477 478 479 480 481 482 483 484 485 486 487 488 489 490 491 492 493 494 495 496 497 498 499 500 501 502 503 504 505 506 507 508 509 510 511 512 513 514 515 516 517 518 519 520 521 522 523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538 539 540 541 542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558 559 560 561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578 579 580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598 599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617 618 619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635 636 637 638 639 640 641 642 643 644 645 646 647 648 649 650 651 652 653 654 655 656 657 658 659 660 661 662 663 664 665 666 667 668 669 670 671 672 673 674 675 676 677 678 679 680 681 682 683 684 685 686 687 688 689 690 691 692 693 694 695 696 697 698 699 700 701 702 703 704 705 706 707 708 709 710 711 712 713 714 715 716 717 718 719 720 721 722 723 724 725 726 727 728 729 730 731 732 733 734 735 736 737 738 739 740 741 742 743 744 745 746 747 748 749 750 751 752 753 754 755 756 757 758 759 760 761 762 763 764 765 766 767 768 769 770 771 772 773 774 775 776 777 778 779 780 781 782 783 784 785 786 787 788 789 790 791 792 793 794 795 796 797 798 799 800 801 802 803 804 805 806 807 808 809 810 811 812 813 814 815 816 817 818 819 820 821 822 823 824 825 826 827 828 829 830 831 832 833 834 835 836 837 838 839 840 841 842 843 844 845 846 847 848 849 850 851 852 853 854 855 856 857 858 859 860 861 862 863 864 865 866 867 868 869 870 871 872 873 874 875 876 877 878 879 880 881 882 883 884 885 886 887 888 889 890 891 892 893 894 895 896 897 898 899 900 901 902 903 904 905 906 907 908 909 910 911 912 913 914 915 916 917 918 919 920 921 922 923 924 925 926 927 928 929 930 931 932 933 934 935 936 937 938 939 940 941 942 943 944 945 946 947 948 949 950 951 952 953 954 955 956 957 958")));
    EXPECT_EQ((string_sequence(28)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28")));
    EXPECT_EQ((string_sequence(29)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29")));
    EXPECT_EQ((string_sequence(26)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26")));
    EXPECT_EQ((string_sequence(6)), (std::string("0 1 2 3 4 5 6")));
    EXPECT_EQ((string_sequence(27)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27")));
    EXPECT_EQ((string_sequence(0)), (std::string("0")));
    EXPECT_EQ((string_sequence(-688)), (std::string("0")));
    EXPECT_EQ((string_sequence(8)), (std::string("0 1 2 3 4 5 6 7 8")));
    EXPECT_EQ((string_sequence(729)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256 257 258 259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294 295 296 297 298 299 300 301 302 303 304 305 306 307 308 309 310 311 312 313 314 315 316 317 318 319 320 321 322 323 324 325 326 327 328 329 330 331 332 333 334 335 336 337 338 339 340 341 342 343 344 345 346 347 348 349 350 351 352 353 354 355 356 357 358 359 360 361 362 363 364 365 366 367 368 369 370 371 372 373 374 375 376 377 378 379 380 381 382 383 384 385 386 387 388 389 390 391 392 393 394 395 396 397 398 399 400 401 402 403 404 405 406 407 408 409 410 411 412 413 414 415 416 417 418 419 420 421 422 423 424 425 426 427 428 429 430 431 432 433 434 435 436 437 438 439 440 441 442 443 444 445 446 447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465 466 467 468 469 470 471 472 473 474 475 476 477 478 479 480 481 482 483 484 485 486 487 488 489 490 491 492 493 494 495 496 497 498 499 500 501 502 503 504 505 506 507 508 509 510 511 512 513 514 515 516 517 518 519 520 521 522 523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538 539 540 541 542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558 559 560 561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578 579 580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598 599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617 618 619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635 636 637 638 639 640 641 642 643 644 645 646 647 648 649 650 651 652 653 654 655 656 657 658 659 660 661 662 663 664 665 666 667 668 669 670 671 672 673 674 675 676 677 678 679 680 681 682 683 684 685 686 687 688 689 690 691 692 693 694 695 696 697 698 699 700 701 702 703 704 705 706 707 708 709 710 711 712 713 714 715 716 717 718 719 720 721 722 723 724 725 726 727 728 729")));
    EXPECT_EQ((string_sequence(11)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11")));
    EXPECT_EQ((string_sequence(10)), (std::string("0 1 2 3 4 5 6 7 8 9 10")));
}
