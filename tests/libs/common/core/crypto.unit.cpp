/**
 * This file is part of Phansar.
 *
 * Copyright (C) 2018  Hansel De La Cruz
 *
 * Phansar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Phansar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <catch2/catch.hpp>
#include <common/core/crypto.hpp>

using namespace common::core::crypto;

TEST_CASE("can hash a string", "[libs][common][core][crypto]") {
    SECTION("using MD5") {
        REQUIRE(hash(hash_type::MD5, "") == "d41d8cd98f00b204e9800998ecf8427e");
    }

    SECTION("using SHA1") {
        REQUIRE(hash(hash_type::SHA1, "") == "da39a3ee5e6b4b0d3255bfef95601890afd80709");
    }

    SECTION("using SHA2-224") {
        REQUIRE(hash(hash_type::SHA2_224, "") ==
                "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f");
    }

    SECTION("using SHA2-256") {
        REQUIRE(hash(hash_type::SHA2_256, "") ==
                "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    }

    SECTION("using SHA2-384") {
        REQUIRE(hash(hash_type::SHA2_384, "") ==
                "38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1"
                "da274edebfe76f65fbd51ad2f14898b95b");
    }

    SECTION("using SHA2-512") {
        REQUIRE(hash(hash_type::SHA2_512, "") ==
                "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47"
                "d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e");
    }

    SECTION("using SHA3-224") {
        REQUIRE(hash(hash_type::SHA3_224, "") ==
                "6b4e03423667dbb73b6e15454f0eb1abd4597f9a1b078e3f5b5a6bc7");
    }

    SECTION("using SHA3-256") {
        REQUIRE(hash(hash_type::SHA3_256, "") ==
                "a7ffc6f8bf1ed76651c14756a061d662f580ff4de43b49fa82d80a4b80f8434a");
    }

    SECTION("using SHA3-384") {
        REQUIRE(hash(hash_type::SHA3_384, "") ==
                "0c63a75b845e4f7d01107d852e4c2485c51a50aaaa94fc61995e71bbee983a"
                "2ac3713831264adb47fb6bd1e058d5f004");
    }

    SECTION("using SHA3-512") {
        REQUIRE(hash(hash_type::SHA3_512, "") ==
                "a69f73cca23a9ac5c8b567dc185a756e97c982164fe25859e0d1dcc1475c80a615"
                "b2123af1f5f94c11e3e9402c3ac558f500199d95b6d3e301758586281dcd26");
    }

    SECTION("using GOST") {
        REQUIRE(hash(hash_type::GOST, "") ==
                "981e5f3ca30c841487830f84fb433e13ac1101569b9c13584ac483234cd656c0");
    }
}

TEST_CASE("can hash a vector of uint8_t", "[libs][common][core][crypto]") {
    std::vector<std::uint8_t> bytes;

    SECTION("using MD5") {
        REQUIRE(hash(hash_type::MD5, bytes) == "d41d8cd98f00b204e9800998ecf8427e");
    }

    SECTION("using SHA1") {
        REQUIRE(hash(hash_type::SHA1, bytes) == "da39a3ee5e6b4b0d3255bfef95601890afd80709");
    }

    SECTION("using SHA2-224") {
        REQUIRE(hash(hash_type::SHA2_224, bytes) ==
                "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f");
    }

    SECTION("using SHA2-256") {
        REQUIRE(hash(hash_type::SHA2_256, bytes) ==
                "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    }

    SECTION("using SHA2-384") {
        REQUIRE(hash(hash_type::SHA2_384, bytes) ==
                "38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1"
                "da274edebfe76f65fbd51ad2f14898b95b");
    }

    SECTION("using SHA2-512") {
        REQUIRE(hash(hash_type::SHA2_512, bytes) ==
                "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47"
                "d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e");
    }

    SECTION("using SHA3-224") {
        REQUIRE(hash(hash_type::SHA3_224, bytes) ==
                "6b4e03423667dbb73b6e15454f0eb1abd4597f9a1b078e3f5b5a6bc7");
    }

    SECTION("using SHA3-256") {
        REQUIRE(hash(hash_type::SHA3_256, bytes) ==
                "a7ffc6f8bf1ed76651c14756a061d662f580ff4de43b49fa82d80a4b80f8434a");
    }

    SECTION("using SHA3-384") {
        REQUIRE(hash(hash_type::SHA3_384, bytes) ==
                "0c63a75b845e4f7d01107d852e4c2485c51a50aaaa94fc61995e71bbee983a"
                "2ac3713831264adb47fb6bd1e058d5f004");
    }

    SECTION("using SHA3-512") {
        REQUIRE(hash(hash_type::SHA3_512, bytes) ==
                "a69f73cca23a9ac5c8b567dc185a756e97c982164fe25859e0d1dcc1475c80a615"
                "b2123af1f5f94c11e3e9402c3ac558f500199d95b6d3e301758586281dcd26");
    }

    SECTION("using GOST") {
        REQUIRE(hash(hash_type::GOST, bytes) ==
                "981e5f3ca30c841487830f84fb433e13ac1101569b9c13584ac483234cd656c0");
    }
}
