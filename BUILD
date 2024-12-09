cc_library(
    name = "hyperloglog",
    hdrs = ["hyperloglog.h"],
    copts = ["-std=c++17"],
)

cc_test(
    name = "hyperloglog_test",
    srcs = ["hyperloglog_test.cc"],
    copts = ["-std=c++17"],
    deps = [
        ":hyperloglog",
    ],
)
