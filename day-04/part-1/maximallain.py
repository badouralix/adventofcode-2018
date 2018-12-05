from runners.python import SubmissionPy
import re

class MaximallainSubmission(SubmissionPy):

	def run(self, s):
		lines = s.split('\n')
		lines = sorted(lines)
		main_dict = {}
		id_temp = -1

		for line in lines :
			info = re.compile("\W+").split(line)

			if info[6] == 'Guard':
				if id_temp != -1 :
					main_dict[id_temp]['count'] += count_temp

				#Stocke l'id
				id_temp = info[7]
				count_temp = 0
				
				if id_temp not in main_dict.keys():
					main_dict[id_temp] = {'count' : 0, 'details' : dict(zip([i for i in range(60)],[0 for i in range(60)]))}
				else : 
					main_dict[id_temp]['count'] += 1

			elif info[6] == 'falls' :
				min_temp = int(info[5])
			else :
				for i in range(min_temp, int(info[5])):
					main_dict[id_temp]['details'][i] += 1
					count_temp += 1

		max_count = 0
		max_id = 0

		for key, value in main_dict.items():
			if value['count'] > max_count :
				max_id = key
				max_count = value['count']

		max_min = 0
		for key, value in main_dict[max_id]['details'].items() :
			if value > max_min :
				max_min = key

		return int(max_id)*int(max_min)

