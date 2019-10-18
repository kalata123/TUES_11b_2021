"""
 Desc:
  Python program to demonstrate the diamond problem
  (a.k.a. Multiple Inheritance)
"""


# Parent class 1
class TeamMember(object):
    def __init__(self, name, uid):
        self.name = name
        self.uid = uid


# Parent class 2
class Leader(object):
    def __init__(self, skill, jobtitle):
        self.skill = skill
        self.jobtitle = jobtitle


# Deriving a child class from the two parent classes
class TeamLeader(TeamMember, Leader):
    def __init__(self, name, uid, skill, jobtitle, exp):
        self.exp = exp
        TeamMember.__init__(self, name, uid)
        Leader.__init__(self, skill, jobtitle)
        print("Name: {}, Skill: {}, Exp: {}"
              .format(self.name, self.skill, self.exp))


TL = TeamLeader('Jake', 10001, "Couching", 'Scrum Master', 5)
