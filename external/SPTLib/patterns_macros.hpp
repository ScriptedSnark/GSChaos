// This file has been automatically generated using autogen_pattern_macros.py

/*
 * Concatenate with empty because otherwise the MSVC preprocessor
 * puts all __VA_ARGS__ arguments into the first one.
 */
#define MAKE_PATTERN_1(name, pattern_name, pattern, ...) static constexpr auto ptn_##name##_1 = PATTERN(pattern);
#define MAKE_PATTERN_2(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_2 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_1(name, __VA_ARGS__), )
#define MAKE_PATTERN_3(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_3 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_2(name, __VA_ARGS__), )
#define MAKE_PATTERN_4(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_4 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_3(name, __VA_ARGS__), )
#define MAKE_PATTERN_5(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_5 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_4(name, __VA_ARGS__), )
#define MAKE_PATTERN_6(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_6 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_5(name, __VA_ARGS__), )
#define MAKE_PATTERN_7(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_7 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_6(name, __VA_ARGS__), )
#define MAKE_PATTERN_8(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_8 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_7(name, __VA_ARGS__), )
#define MAKE_PATTERN_9(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_9 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_8(name, __VA_ARGS__), )
#define MAKE_PATTERN_10(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_10 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_9(name, __VA_ARGS__), )
#define MAKE_PATTERN_11(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_11 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_10(name, __VA_ARGS__), )
#define MAKE_PATTERN_12(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_12 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_11(name, __VA_ARGS__), )
#define MAKE_PATTERN_13(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_13 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_12(name, __VA_ARGS__), )
#define MAKE_PATTERN_14(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_14 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_13(name, __VA_ARGS__), )
#define MAKE_PATTERN_15(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_15 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_14(name, __VA_ARGS__), )
#define MAKE_PATTERN_16(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_16 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_15(name, __VA_ARGS__), )
#define MAKE_PATTERN_17(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_17 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_16(name, __VA_ARGS__), )
#define MAKE_PATTERN_18(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_18 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_17(name, __VA_ARGS__), )
#define MAKE_PATTERN_19(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_19 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_18(name, __VA_ARGS__), )
#define MAKE_PATTERN_20(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_20 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_19(name, __VA_ARGS__), )
#define MAKE_PATTERN_21(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_21 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_20(name, __VA_ARGS__), )
#define MAKE_PATTERN_22(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_22 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_21(name, __VA_ARGS__), )
#define MAKE_PATTERN_23(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_23 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_22(name, __VA_ARGS__), )
#define MAKE_PATTERN_24(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_24 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_23(name, __VA_ARGS__), )
#define MAKE_PATTERN_25(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_25 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_24(name, __VA_ARGS__), )
#define MAKE_PATTERN_26(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_26 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_25(name, __VA_ARGS__), )
#define MAKE_PATTERN_27(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_27 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_26(name, __VA_ARGS__), )
#define MAKE_PATTERN_28(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_28 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_27(name, __VA_ARGS__), )
#define MAKE_PATTERN_29(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_29 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_28(name, __VA_ARGS__), )
#define MAKE_PATTERN_30(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_30 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_29(name, __VA_ARGS__), )
#define MAKE_PATTERN_31(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_31 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_30(name, __VA_ARGS__), )
#define MAKE_PATTERN_32(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_32 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_31(name, __VA_ARGS__), )
#define MAKE_PATTERN_33(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_33 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_32(name, __VA_ARGS__), )
#define MAKE_PATTERN_34(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_34 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_33(name, __VA_ARGS__), )
#define MAKE_PATTERN_35(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_35 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_34(name, __VA_ARGS__), )
#define MAKE_PATTERN_36(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_36 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_35(name, __VA_ARGS__), )
#define MAKE_PATTERN_37(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_37 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_36(name, __VA_ARGS__), )
#define MAKE_PATTERN_38(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_38 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_37(name, __VA_ARGS__), )
#define MAKE_PATTERN_39(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_39 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_38(name, __VA_ARGS__), )
#define MAKE_PATTERN_40(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_40 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_39(name, __VA_ARGS__), )
#define MAKE_PATTERN_41(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_41 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_40(name, __VA_ARGS__), )
#define MAKE_PATTERN_42(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_42 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_41(name, __VA_ARGS__), )
#define MAKE_PATTERN_43(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_43 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_42(name, __VA_ARGS__), )
#define MAKE_PATTERN_44(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_44 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_43(name, __VA_ARGS__), )
#define MAKE_PATTERN_45(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_45 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_44(name, __VA_ARGS__), )
#define MAKE_PATTERN_46(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_46 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_45(name, __VA_ARGS__), )
#define MAKE_PATTERN_47(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_47 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_46(name, __VA_ARGS__), )
#define MAKE_PATTERN_48(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_48 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_47(name, __VA_ARGS__), )
#define MAKE_PATTERN_49(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_49 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_48(name, __VA_ARGS__), )
#define MAKE_PATTERN_50(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_50 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_49(name, __VA_ARGS__), )
#define MAKE_PATTERN_51(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_51 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_50(name, __VA_ARGS__), )
#define MAKE_PATTERN_52(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_52 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_51(name, __VA_ARGS__), )
#define MAKE_PATTERN_53(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_53 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_52(name, __VA_ARGS__), )
#define MAKE_PATTERN_54(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_54 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_53(name, __VA_ARGS__), )
#define MAKE_PATTERN_55(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_55 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_54(name, __VA_ARGS__), )
#define MAKE_PATTERN_56(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_56 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_55(name, __VA_ARGS__), )
#define MAKE_PATTERN_57(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_57 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_56(name, __VA_ARGS__), )
#define MAKE_PATTERN_58(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_58 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_57(name, __VA_ARGS__), )
#define MAKE_PATTERN_59(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_59 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_58(name, __VA_ARGS__), )
#define MAKE_PATTERN_60(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_60 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_59(name, __VA_ARGS__), )
#define MAKE_PATTERN_61(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_61 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_60(name, __VA_ARGS__), )
#define MAKE_PATTERN_62(name, pattern_name, pattern, ...)     \
	static constexpr auto ptn_##name##_62 = PATTERN(pattern); \
	CONCATENATE(MAKE_PATTERN_61(name, __VA_ARGS__), )
#ifdef _MSC_VER
#define NAME_PATTERN_1(name, pattern_name, pattern, ...) \
	PatternWrapper { pattern_name, ptn_##name##_1 }
#define NAME_PATTERN_2(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_2}, CONCATENATE(NAME_PATTERN_1(name, __VA_ARGS__), )
#define NAME_PATTERN_3(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_3}, CONCATENATE(NAME_PATTERN_2(name, __VA_ARGS__), )
#define NAME_PATTERN_4(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_4}, CONCATENATE(NAME_PATTERN_3(name, __VA_ARGS__), )
#define NAME_PATTERN_5(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_5}, CONCATENATE(NAME_PATTERN_4(name, __VA_ARGS__), )
#define NAME_PATTERN_6(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_6}, CONCATENATE(NAME_PATTERN_5(name, __VA_ARGS__), )
#define NAME_PATTERN_7(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_7}, CONCATENATE(NAME_PATTERN_6(name, __VA_ARGS__), )
#define NAME_PATTERN_8(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_8}, CONCATENATE(NAME_PATTERN_7(name, __VA_ARGS__), )
#define NAME_PATTERN_9(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_9}, CONCATENATE(NAME_PATTERN_8(name, __VA_ARGS__), )
#define NAME_PATTERN_10(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_10}, CONCATENATE(NAME_PATTERN_9(name, __VA_ARGS__), )
#define NAME_PATTERN_11(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_11}, CONCATENATE(NAME_PATTERN_10(name, __VA_ARGS__), )
#define NAME_PATTERN_12(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_12}, CONCATENATE(NAME_PATTERN_11(name, __VA_ARGS__), )
#define NAME_PATTERN_13(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_13}, CONCATENATE(NAME_PATTERN_12(name, __VA_ARGS__), )
#define NAME_PATTERN_14(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_14}, CONCATENATE(NAME_PATTERN_13(name, __VA_ARGS__), )
#define NAME_PATTERN_15(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_15}, CONCATENATE(NAME_PATTERN_14(name, __VA_ARGS__), )
#define NAME_PATTERN_16(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_16}, CONCATENATE(NAME_PATTERN_15(name, __VA_ARGS__), )
#define NAME_PATTERN_17(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_17}, CONCATENATE(NAME_PATTERN_16(name, __VA_ARGS__), )
#define NAME_PATTERN_18(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_18}, CONCATENATE(NAME_PATTERN_17(name, __VA_ARGS__), )
#define NAME_PATTERN_19(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_19}, CONCATENATE(NAME_PATTERN_18(name, __VA_ARGS__), )
#define NAME_PATTERN_20(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_20}, CONCATENATE(NAME_PATTERN_19(name, __VA_ARGS__), )
#define NAME_PATTERN_21(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_21}, CONCATENATE(NAME_PATTERN_20(name, __VA_ARGS__), )
#define NAME_PATTERN_22(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_22}, CONCATENATE(NAME_PATTERN_21(name, __VA_ARGS__), )
#define NAME_PATTERN_23(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_23}, CONCATENATE(NAME_PATTERN_22(name, __VA_ARGS__), )
#define NAME_PATTERN_24(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_24}, CONCATENATE(NAME_PATTERN_23(name, __VA_ARGS__), )
#define NAME_PATTERN_25(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_25}, CONCATENATE(NAME_PATTERN_24(name, __VA_ARGS__), )
#define NAME_PATTERN_26(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_26}, CONCATENATE(NAME_PATTERN_25(name, __VA_ARGS__), )
#define NAME_PATTERN_27(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_27}, CONCATENATE(NAME_PATTERN_26(name, __VA_ARGS__), )
#define NAME_PATTERN_28(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_28}, CONCATENATE(NAME_PATTERN_27(name, __VA_ARGS__), )
#define NAME_PATTERN_29(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_29}, CONCATENATE(NAME_PATTERN_28(name, __VA_ARGS__), )
#define NAME_PATTERN_30(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_30}, CONCATENATE(NAME_PATTERN_29(name, __VA_ARGS__), )
#define NAME_PATTERN_31(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_31}, CONCATENATE(NAME_PATTERN_30(name, __VA_ARGS__), )
#define NAME_PATTERN_32(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_32}, CONCATENATE(NAME_PATTERN_31(name, __VA_ARGS__), )
#define NAME_PATTERN_33(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_33}, CONCATENATE(NAME_PATTERN_32(name, __VA_ARGS__), )
#define NAME_PATTERN_34(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_34}, CONCATENATE(NAME_PATTERN_33(name, __VA_ARGS__), )
#define NAME_PATTERN_35(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_35}, CONCATENATE(NAME_PATTERN_34(name, __VA_ARGS__), )
#define NAME_PATTERN_36(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_36}, CONCATENATE(NAME_PATTERN_35(name, __VA_ARGS__), )
#define NAME_PATTERN_37(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_37}, CONCATENATE(NAME_PATTERN_36(name, __VA_ARGS__), )
#define NAME_PATTERN_38(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_38}, CONCATENATE(NAME_PATTERN_37(name, __VA_ARGS__), )
#define NAME_PATTERN_39(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_39}, CONCATENATE(NAME_PATTERN_38(name, __VA_ARGS__), )
#define NAME_PATTERN_40(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_40}, CONCATENATE(NAME_PATTERN_39(name, __VA_ARGS__), )
#define NAME_PATTERN_41(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_41}, CONCATENATE(NAME_PATTERN_40(name, __VA_ARGS__), )
#define NAME_PATTERN_42(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_42}, CONCATENATE(NAME_PATTERN_41(name, __VA_ARGS__), )
#define NAME_PATTERN_43(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_43}, CONCATENATE(NAME_PATTERN_42(name, __VA_ARGS__), )
#define NAME_PATTERN_44(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_44}, CONCATENATE(NAME_PATTERN_43(name, __VA_ARGS__), )
#define NAME_PATTERN_45(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_45}, CONCATENATE(NAME_PATTERN_44(name, __VA_ARGS__), )
#define NAME_PATTERN_46(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_46}, CONCATENATE(NAME_PATTERN_45(name, __VA_ARGS__), )
#define NAME_PATTERN_47(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_47}, CONCATENATE(NAME_PATTERN_46(name, __VA_ARGS__), )
#define NAME_PATTERN_48(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_48}, CONCATENATE(NAME_PATTERN_47(name, __VA_ARGS__), )
#define NAME_PATTERN_49(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_49}, CONCATENATE(NAME_PATTERN_48(name, __VA_ARGS__), )
#define NAME_PATTERN_50(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_50}, CONCATENATE(NAME_PATTERN_49(name, __VA_ARGS__), )
#define NAME_PATTERN_51(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_51}, CONCATENATE(NAME_PATTERN_50(name, __VA_ARGS__), )
#define NAME_PATTERN_52(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_52}, CONCATENATE(NAME_PATTERN_51(name, __VA_ARGS__), )
#define NAME_PATTERN_53(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_53}, CONCATENATE(NAME_PATTERN_52(name, __VA_ARGS__), )
#define NAME_PATTERN_54(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_54}, CONCATENATE(NAME_PATTERN_53(name, __VA_ARGS__), )
#define NAME_PATTERN_55(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_55}, CONCATENATE(NAME_PATTERN_54(name, __VA_ARGS__), )
#define NAME_PATTERN_56(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_56}, CONCATENATE(NAME_PATTERN_55(name, __VA_ARGS__), )
#define NAME_PATTERN_57(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_57}, CONCATENATE(NAME_PATTERN_56(name, __VA_ARGS__), )
#define NAME_PATTERN_58(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_58}, CONCATENATE(NAME_PATTERN_57(name, __VA_ARGS__), )
#define NAME_PATTERN_59(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_59}, CONCATENATE(NAME_PATTERN_58(name, __VA_ARGS__), )
#define NAME_PATTERN_60(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_60}, CONCATENATE(NAME_PATTERN_59(name, __VA_ARGS__), )
#define NAME_PATTERN_61(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_61}, CONCATENATE(NAME_PATTERN_60(name, __VA_ARGS__), )
#define NAME_PATTERN_62(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_62}, CONCATENATE(NAME_PATTERN_61(name, __VA_ARGS__), )
#else
#define NAME_PATTERN_1(name, pattern_name, pattern, ...) \
	PatternWrapper { pattern_name, ptn_##name##_1 }
#define NAME_PATTERN_2(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_2}, NAME_PATTERN_1(name, __VA_ARGS__)
#define NAME_PATTERN_3(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_3}, NAME_PATTERN_2(name, __VA_ARGS__)
#define NAME_PATTERN_4(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_4}, NAME_PATTERN_3(name, __VA_ARGS__)
#define NAME_PATTERN_5(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_5}, NAME_PATTERN_4(name, __VA_ARGS__)
#define NAME_PATTERN_6(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_6}, NAME_PATTERN_5(name, __VA_ARGS__)
#define NAME_PATTERN_7(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_7}, NAME_PATTERN_6(name, __VA_ARGS__)
#define NAME_PATTERN_8(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_8}, NAME_PATTERN_7(name, __VA_ARGS__)
#define NAME_PATTERN_9(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_9}, NAME_PATTERN_8(name, __VA_ARGS__)
#define NAME_PATTERN_10(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_10}, NAME_PATTERN_9(name, __VA_ARGS__)
#define NAME_PATTERN_11(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_11}, NAME_PATTERN_10(name, __VA_ARGS__)
#define NAME_PATTERN_12(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_12}, NAME_PATTERN_11(name, __VA_ARGS__)
#define NAME_PATTERN_13(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_13}, NAME_PATTERN_12(name, __VA_ARGS__)
#define NAME_PATTERN_14(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_14}, NAME_PATTERN_13(name, __VA_ARGS__)
#define NAME_PATTERN_15(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_15}, NAME_PATTERN_14(name, __VA_ARGS__)
#define NAME_PATTERN_16(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_16}, NAME_PATTERN_15(name, __VA_ARGS__)
#define NAME_PATTERN_17(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_17}, NAME_PATTERN_16(name, __VA_ARGS__)
#define NAME_PATTERN_18(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_18}, NAME_PATTERN_17(name, __VA_ARGS__)
#define NAME_PATTERN_19(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_19}, NAME_PATTERN_18(name, __VA_ARGS__)
#define NAME_PATTERN_20(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_20}, NAME_PATTERN_19(name, __VA_ARGS__)
#define NAME_PATTERN_21(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_21}, NAME_PATTERN_20(name, __VA_ARGS__)
#define NAME_PATTERN_22(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_22}, NAME_PATTERN_21(name, __VA_ARGS__)
#define NAME_PATTERN_23(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_23}, NAME_PATTERN_22(name, __VA_ARGS__)
#define NAME_PATTERN_24(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_24}, NAME_PATTERN_23(name, __VA_ARGS__)
#define NAME_PATTERN_25(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_25}, NAME_PATTERN_24(name, __VA_ARGS__)
#define NAME_PATTERN_26(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_26}, NAME_PATTERN_25(name, __VA_ARGS__)
#define NAME_PATTERN_27(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_27}, NAME_PATTERN_26(name, __VA_ARGS__)
#define NAME_PATTERN_28(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_28}, NAME_PATTERN_27(name, __VA_ARGS__)
#define NAME_PATTERN_29(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_29}, NAME_PATTERN_28(name, __VA_ARGS__)
#define NAME_PATTERN_30(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_30}, NAME_PATTERN_29(name, __VA_ARGS__)
#define NAME_PATTERN_31(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_31}, NAME_PATTERN_30(name, __VA_ARGS__)
#define NAME_PATTERN_32(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_32}, NAME_PATTERN_31(name, __VA_ARGS__)
#define NAME_PATTERN_33(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_33}, NAME_PATTERN_32(name, __VA_ARGS__)
#define NAME_PATTERN_34(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_34}, NAME_PATTERN_33(name, __VA_ARGS__)
#define NAME_PATTERN_35(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_35}, NAME_PATTERN_34(name, __VA_ARGS__)
#define NAME_PATTERN_36(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_36}, NAME_PATTERN_35(name, __VA_ARGS__)
#define NAME_PATTERN_37(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_37}, NAME_PATTERN_36(name, __VA_ARGS__)
#define NAME_PATTERN_38(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_38}, NAME_PATTERN_37(name, __VA_ARGS__)
#define NAME_PATTERN_39(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_39}, NAME_PATTERN_38(name, __VA_ARGS__)
#define NAME_PATTERN_40(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_40}, NAME_PATTERN_39(name, __VA_ARGS__)
#define NAME_PATTERN_41(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_41}, NAME_PATTERN_40(name, __VA_ARGS__)
#define NAME_PATTERN_42(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_42}, NAME_PATTERN_41(name, __VA_ARGS__)
#define NAME_PATTERN_43(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_43}, NAME_PATTERN_42(name, __VA_ARGS__)
#define NAME_PATTERN_44(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_44}, NAME_PATTERN_43(name, __VA_ARGS__)
#define NAME_PATTERN_45(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_45}, NAME_PATTERN_44(name, __VA_ARGS__)
#define NAME_PATTERN_46(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_46}, NAME_PATTERN_45(name, __VA_ARGS__)
#define NAME_PATTERN_47(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_47}, NAME_PATTERN_46(name, __VA_ARGS__)
#define NAME_PATTERN_48(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_48}, NAME_PATTERN_47(name, __VA_ARGS__)
#define NAME_PATTERN_49(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_49}, NAME_PATTERN_48(name, __VA_ARGS__)
#define NAME_PATTERN_50(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_50}, NAME_PATTERN_49(name, __VA_ARGS__)
#define NAME_PATTERN_51(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_51}, NAME_PATTERN_50(name, __VA_ARGS__)
#define NAME_PATTERN_52(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_52}, NAME_PATTERN_51(name, __VA_ARGS__)
#define NAME_PATTERN_53(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_53}, NAME_PATTERN_52(name, __VA_ARGS__)
#define NAME_PATTERN_54(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_54}, NAME_PATTERN_53(name, __VA_ARGS__)
#define NAME_PATTERN_55(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_55}, NAME_PATTERN_54(name, __VA_ARGS__)
#define NAME_PATTERN_56(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_56}, NAME_PATTERN_55(name, __VA_ARGS__)
#define NAME_PATTERN_57(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_57}, NAME_PATTERN_56(name, __VA_ARGS__)
#define NAME_PATTERN_58(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_58}, NAME_PATTERN_57(name, __VA_ARGS__)
#define NAME_PATTERN_59(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_59}, NAME_PATTERN_58(name, __VA_ARGS__)
#define NAME_PATTERN_60(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_60}, NAME_PATTERN_59(name, __VA_ARGS__)
#define NAME_PATTERN_61(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_61}, NAME_PATTERN_60(name, __VA_ARGS__)
#define NAME_PATTERN_62(name, pattern_name, pattern, ...) PatternWrapper{pattern_name, ptn_##name##_62}, NAME_PATTERN_61(name, __VA_ARGS__)
#endif // _MSC_VER
#define FOR_EACH2_ARG_N(__1, __1_, __2, __2_, __3, __3_, __4, __4_, __5, __5_, __6, __6_, __7, __7_, __8, __8_, __9, __9_, __10, __10_, __11, __11_, __12, __12_, __13, __13_, __14, __14_, __15, __15_, __16, __16_, __17, __17_, __18, __18_, __19, __19_, __20, __20_, __21, __21_, __22, __22_, __23, __23_, __24, __24_, __25, __25_, __26, __26_, __27, __27_, __28, __28_, __29, __29_, __30, __30_, __31, __31_, __32, __32_, __33, __33_, __34, __34_, __35, __35_, __36, __36_, __37, __37_, __38, __38_, __39, __39_, __40, __40_, __41, __41_, __42, __42_, __43, __43_, __44, __44_, __45, __45_, __46, __46_, __47, __47_, __48, __48_, __49, __49_, __50, __50_, __51, __51_, __52, __52_, __53, __53_, __54, __54_, __55, __55_, __56, __56_, __57, __57_, __58, __58_, __59, __59_, __60, __60_, __61, __61_, __62, __62_, N, ...) N
#define FOR_EACH2_RSEQ_N 62, 0, 61, 0, 60, 0, 59, 0, 58, 0, 57, 0, 56, 0, 55, 0, 54, 0, 53, 0, 52, 0, 51, 0, 50, 0, 49, 0, 48, 0, 47, 0, 46, 0, 45, 0, 44, 0, 43, 0, 42, 0, 41, 0, 40, 0, 39, 0, 38, 0, 37, 0, 36, 0, 35, 0, 34, 0, 33, 0, 32, 0, 31, 0, 30, 0, 29, 0, 28, 0, 27, 0, 26, 0, 25, 0, 24, 0, 23, 0, 22, 0, 21, 0, 20, 0, 19, 0, 18, 0, 17, 0, 16, 0, 15, 0, 14, 0, 13, 0, 12, 0, 11, 0, 10, 0, 9, 0, 8, 0, 7, 0, 6, 0, 5, 0, 4, 0, 3, 0, 2, 0, 1
