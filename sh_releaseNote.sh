#!/bin/bash

##################### 릴리즈 태그, 노트 작성 가이드 gunoo22 241024 ##########################
### 릴리즈 태그 명령어
#태그 fetch
#git fetch --tags

#태그 설정
#git tag -a v1.3.29.1 9fadaf -m "Release version v1.3.29.1"

#태그 Push
#git push origin --tags

#태그 삭제
#git tag -d <tagname>

#원격저장소 태그 삭제
#git push origin --delete <tagname>
### /릴리즈 태그 명령어

### 릴리즈 노트 작성
# 릴리즈 시작 커밋
#START_COMMIT="46f938"
# 릴리즈 끝 커밋
#END_COMMIT="47dcc5"

# 커밋 로그 추출
#git log --pretty=format:"- %s" $START_COMMIT..$END_COMMIT > release_notes/v1.3.29.1.txt

# 커밋 로그 추출 (한개의 커밋만)
# git log 9fadaf -n 1 --pretty=format:"%s%n%n%b" > release_notes/v1.3.29.1.txt

# 릴리즈 노트 파일 확인
#cat release_notes/v1.3.29.1.txt
### /릴리즈 노트 작성
##################### /릴리즈 태그, 노트 작성 가이드 gunoo22 241024 ##########################

### 릴리즈 노트 작성
# 릴리즈 시작 커밋
START_COMMIT="3cb5b6e1"
# 릴리즈 끝 커밋
END_COMMIT="4ed90231"

# 커밋 로그 추출
git log --pretty=format:"- %s" $START_COMMIT..$END_COMMIT > release_notes/v1.3.30.0_UCPID/차세대자동차.txt

# 커밋 로그 추출 (한개의 커밋만)
#git log 9fadaf6686eeea756ebadf78d8618a7278f50c34 -n 1 --pretty=format:"%s%n%n%b" > release_notes/v1.3.29.3_Lib타임아웃.txt

# 릴리즈 노트 파일 확인
cat release_notes/v1.3.30.0_UCPID/차세대자동차.txt
### /릴리즈 노트 작성