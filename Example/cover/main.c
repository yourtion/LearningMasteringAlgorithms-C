//
//  main.c
//  MasteringAlgorithms
//  Illustrates set covering (see Chapter 7).
//
//  Created by YourtionGuo on 26/04/2017.
//  Copyright © 2017 Yourtion. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cover.h"
#include "list.h"
#include "set.h"

/// 定义技能与玩家常量
#define   SKILLS_COUNT    12
#define   PLAYER_COUNT    8


static void print_skills(const Set *skills)
{
  ListElmt    *member;
  char        *data;
  int         size, i;
  
  /// 打印玩家技能集合
  fprintf(stdout, "--> Set size is %d\n", size = set_size(skills));
  
  i = 0;
  member = list_head(skills);
  
  while (i < size) {
    
    data = list_data(member);
    fprintf(stdout, "---> skills[%03d]=%c\n", i, *data);
    member = list_next(member);
    i++;
    
  }
  
  return;
}

static void print_players(const Set *players)
{
  ListElmt      *member;
  
  /// 打印玩家
  for (member = list_head(players); member != NULL; member = list_next(member)){
    
    fprintf(stdout, "-> Player %c\n", *(char *)((KSet *)list_data(member))->key);
    print_skills(&((KSet *)list_data(member))->set);
    
  }
  
  return;
}

int match_key(const void *key1, const void *key2)
{
  /// 判断两个 key 是否相等
  if (*(char *)((const KSet *)key1)->key == *(char *)((const KSet *)key2)->key) return 1;
  
  return 0;
}

int match_skill(const void *skill1, const void *skill2)
{
  /// 判断两个 skill 是否相等
  if (*(const char *)skill1 == *(const char *)skill2) return 1;
  
  return 0;
}

int main(int argc, char **argv)
{
  Set       skills, players, covering;
  char      skills_array[SKILLS_COUNT], subids_array[PLAYER_COUNT];
  KSet      player_array[PLAYER_COUNT];
  int       retval, i;
  
  /// 初始化技能集合
  fprintf(stdout, "Creating the set of skills\n");
  
  set_init(&skills, match_skill, NULL);
  
  skills_array[0] = 'a';
  skills_array[1] = 'b';
  skills_array[2] = 'c';
  skills_array[3] = 'd';
  skills_array[4] = 'e';
  skills_array[5] = 'f';
  skills_array[6] = 'g';
  skills_array[7] = 'h';
  skills_array[8] = 'i';
  skills_array[9] = 'j';
  skills_array[10] = 'k';
  skills_array[11] = 'l';
  
  for (i = 0; i < SKILLS_COUNT; i++) {
    
    if (set_insert(&skills, &skills_array[i]) != 0) return 1;
    
  }
  
  print_skills(&skills);
  
  /// 创建玩家并赋予相应技能
  
  fprintf(stdout, "Creating the player subsets\n");
  
  set_init(&players, match_key, NULL);
  
  subids_array[0] = '1';
  subids_array[1] = '2';
  subids_array[2] = '3';
  subids_array[3] = '4';
  subids_array[4] = '5';
  subids_array[5] = '6';
  subids_array[6] = '7';
  subids_array[7] = '8';
  
  for (i = 0; i < PLAYER_COUNT; i++) {
    
    player_array[i].key = &subids_array[i];
    set_init(&player_array[i].set, match_skill, NULL);
    
    switch (i) {
        
      case 0:
        
        if (set_insert(&player_array[i].set, &skills_array[0]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[1]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[2]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[3]) != 0) return 1;
        
        break;
        
      case 1:
        
        if (set_insert(&player_array[i].set, &skills_array[4]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[5]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[6]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[7]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[8]) != 0) return 1;
        
        break;
        
      case 2:
        
        if (set_insert(&player_array[i].set, &skills_array[9]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[10]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[11]) != 0) return 1;
        
        break;
        
      case 3:
        
        if (set_insert(&player_array[i].set, &skills_array[0]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[4]) != 0) return 1;
        
        break;
        
      case 4:
        
        if (set_insert(&player_array[i].set, &skills_array[1]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[5]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[6]) != 0) return 1;
        
        break;
        
      case 5:
        
        if (set_insert(&player_array[i].set, &skills_array[2]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[3]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[6]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[7]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[10]) != 0) return 1;
        if (set_insert(&player_array[i].set, &skills_array[11]) != 0) return 1;
        
        break;
        
      default:
        
        if (set_insert(&player_array[i].set, &skills_array[11]) != 0) return 1;
        
    }
    
    if (set_insert(&players, &player_array[i]) != 0) return 1;
    
  }
  
  print_players(&players);
  
  /// 计算集合覆盖
  
  fprintf(stdout, "Generating the cover\n");
  
  if ((retval = cover(&skills, &players, &covering)) != 0) return 1;
  
  if (retval == 1) {
    fprintf(stderr, "The set could not be covered\n");
  }
  else {
    print_players(&covering);
  }
  
  /// 销毁相关集合

  fprintf(stdout, "Destroying the sets\n");
  
  for (i = 0; i < PLAYER_COUNT; i++) {
    set_destroy(&player_array[i].set);
  }
  
  set_destroy(&skills);
  
  return 0;
}
