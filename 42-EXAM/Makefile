# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rerodrig <rerodrig@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/21 01:05:24 by jcluzet           #+#    #+#              #
#    Updated: 2025/12/16 14:37:15 by rerodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@bash .system/launch.sh all

re: clean
	@bash .system/launch.sh

gradejustinstall:
	@bash .system/launch.sh gradejustinstall

grade: clean
	@bash .system/launch.sh grade

migrate_exam05:
	@echo "Migrating exam_05 to new structure..."
	@if [ -d "0_new_exams/exam_05" ]; then \
		if [ -d ".subjects/STUD_PART/exam_05" ]; then \
			echo "Backing up old exam_05..."; \
			mv .subjects/STUD_PART/exam_05 .subjects/STUD_PART/exam_05_old_backup; \
		fi; \
		echo "Moving new exam_05 into place..."; \
		cp -r 0_new_exams/exam_05 .subjects/STUD_PART/; \
		echo "✅ Exam_05 migration completed!"; \
		echo "Old exam backed up as exam_05_old_backup"; \
	else \
		echo "❌ 0_new_exams/exam_05 not found!"; \''
	fi

clean:
	@rm -rf .system/a.out
	@rm -rf .system/a.out.dSYM

fclean:
	@rm .system/a.out

help:
	@echo "\x1B[37mType \x1B[32m> make \x1B[37mto start the exam"
	@echo "\x1B[37mType \x1B[32m> make migrate_exam05 \x1B[37mto replace old exam_05 with new structure"