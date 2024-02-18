PYTHON = python3
PIP = pip

MANAGE_FILE = manage.py

EXAM-ASSESSMENT_DIR = exam-assessment
API_DIR = api
SCRIPTS_DIR = scripts

.DEFAULT_GOAL = run
.PHONY: run setup setupdb makemigrations migrate runserver install createuser createdb clean

run: makemigrations migrate runserver

setup: install createuser createdb

setupdb: createuser createdb


makemigrations:
	$(PYTHON) $(MANAGE_FILE) makemigrations api

migrate:
	$(PYTHON) $(MANAGE_FILE) migrate

runserver:
	$(PYTHON) $(MANAGE_FILE) runserver


install:
	sudo apt-get install python3-dev default-libmysqlclient-dev build-essential pkg-config; \
	$(PIP) install --upgrade $(PIP); \
	$(PIP) install -r requirements.txt; \
	$(PYTHON) -m spacy download pt_core_news_sm;

createuser:
	sudo mysql -u root -p < $(SCRIPTS_DIR)/create_user.sql

createdb:
	mysql -u ras-7b -p'ras-7b' -e "CREATE DATABASE IF NOT EXISTS exam_assessment;"


clean:
	rm -rf $(EXAM-ASSESSMENT_DIR)/__pycache__
	rm -rf $(API_DIR)/migrations
	rm -rf $(API_DIR)/__pycache__
