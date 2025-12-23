
all:
	@bash exam.sh

re: fclean all



clean:
	rm -f .resources/rank05/level1/bigint/ref_bigint \
		.resources/rank05/level1/bigint/user_bigint \
		.resources/rank05/level1/bigint/user_main.cpp \
		.resources/rank05/level1/bigint/user_bigint.hpp \
		.resources/rank05/level1/bigint/user_bigint.cpp \
		.resources/rank05/level1/bigint/ref_output.txt \
		.resources/rank05/level1/bigint/user_output.txt \
		.resources/rank05/level1/polyset/ref_polyset \
		.resources/rank05/level1/polyset/user_polyset \
		.resources/rank05/level1/polyset/user_main.cpp \
		.resources/rank05/level1/polyset/ref_output.txt \
		.resources/rank05/level1/polyset/user_output.txt \
		.resources/rank05/level1/vect2/ref_vect2 \
		.resources/rank05/level1/vect2/user_vect2 \
		.resources/rank05/level1/vect2/user_main.cpp \
		.resources/rank05/level1/vect2/user_vect2.hpp \
		.resources/rank05/level1/vect2/user_vect2.cpp \
		.resources/rank05/level1/vect2/ref_output.txt \
		.resources/rank05/level1/vect2/user_output.txt \
		.resources/rank05/level1/bigint/tester_output.log \
		.resources/rank05/level1/polyset/tester_output.log \
		.resources/rank05/level1/vect2/tester_output.log
	@if [ -d rendu ]; then \
	  mkdir -p tryed; \
	  ts=$$(date +%Y%m%d_%H%M%S); \
	  mv rendu tryed/rendu_$$ts; \
	fi

fclean: clean
	@if [ -d rendu ]; then \
	  mkdir -p tryed; \
	  ts=$$(date +%Y%m%d_%H%M%S); \
	  mv rendu tryed/rendu_$$ts; \
	fi
