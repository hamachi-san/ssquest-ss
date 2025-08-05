# ユニティのパス（適宜変更）
UNITY_ROOT := ../third_party/unity

# コンパイラとフラグ
CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -DUNIT_TEST -I$(UNITY_ROOT) -I../src -I.

# ユニットテスト対象のプロダクトコード（明示的に指定）
SRC_UNDER_TEST := \
  ../src/common/hash_map.c \
  ../src/wrapper/memory.c

# テストコード（test_*.c）を再帰的に収集
TEST_SRCS := $(shell find . -name 'test_*.c')

# 出力ファイル
TARGET := run_tests

# 中間オブジェクトファイル
OBJS := $(SRC_UNDER_TEST:.c=.o) $(TEST_SRCS:.c=.o) $(UNITY_ROOT)/unity.o

# デフォルトターゲット
all: $(TARGET)

# 実行ファイル生成
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

# 一般的な .c → .o ルール
%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Unity のビルド（手動で unity.c を指定する場合）
$(UNITY_ROOT)/unity.o: $(UNITY_ROOT)/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

# テストの実行
test: all
	./$(TARGET)

# クリーン
clean:
	rm -f $(TARGET) $(OBJS) $(UNITY_ROOT)/unity.o
	find . -name '*.o' -delete

.PHONY: all test clean
