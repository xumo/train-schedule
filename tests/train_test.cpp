#include <gtest/gtest.h>


#include <controllers/JsonWriter.h>

TEST(Trains, TRAIN_JSON){
    Train t{1, PASSENGER, "Union Express"};
    auto node = JsonWriter::trainToJson(t);

    std::string expected = "{\"name\":\"Union Express\",\"number\":1,\"type\":\"PASSENGER\"}";
    ASSERT_EQ(node.dump(), expected);
}