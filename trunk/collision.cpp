int min_value_index(float array[4]);
void sort_array(int*);

void collision_box(box * boks1, box * boks2) {
	Vector * v;
	for (int x = 0; x < 4; ++x) {
		v = boks1->inside(boks2->points[x].pos);
		if (v != 0) {
			float lengths[4];
			for (int z = 0; z < 4; ++z) 
				lengths[z] = (boks2->points[x].pos-boks1->points[z].pos).length();
			
			int top_lengths_index[2];
			float L1, L2, L;
			
			top_lengths_index[0] = min_value_index(lengths);
			L1 = lengths[top_lengths_index[0]];
			lengths[min_value_index(lengths)] = 294967296;
			
			top_lengths_index[1] = min_value_index(lengths);
			L2 = lengths[top_lengths_index[1]];
			L = L1 + L2;
			
			sort_array(top_lengths_index);
			
			float f1, f2;
			f1 = L2 / L;
			f2 = L1 / L;
			
			Vector side_per = (boks1->points[top_lengths_index[1]].pos - boks1->points[top_lengths_index[0]].pos);
			float b = side_per.length();
			
			float dist = sin(acos(
				(pow(b,2)+pow(L1,2)-pow(L2,2)) /
						(2*b*L1)
			)) * L1;
			
			/*Vector move_vec (
				boks1->points[top_lengths_index[0]]->pos.x - v[top_lengths_index[0]].x,
				boks1->points[top_lengths_index[0]]->pos.y - v[top_lengths_index[0]].y);
			move_vec.set_length(dist);
			move_vec = -move_vec;*/
			
			Vector move_vec = side_per.ccper();
			move_vec.set_length(dist);
			
			boks1->points[top_lengths_index[0]].attract_to(move_vec*f1);
			boks1->points[top_lengths_index[1]].attract_to(move_vec*f2);
			boks2->points[x].attract_to(-(move_vec));
		}
	}
}

int min_value_index(float array[4])
{
     int min = array[0];
     int index = 0;

     for(int i = 1; i < 4; i++)
     {
          	if(array[i] < min) {
                min = array[i];
                index = i;
			}
     }
     return index;
}

void sort_array(int * list) {
	int temp;
	if (list[0]==3) {
		if (list[1]==0) return;
	}
	else if (list[1]==3) {
		if (list[0]==0) {
			list[0] = 3;
			list[1] = 0;
			return;
		}
	}
	if (list[0] > list[1]) {
		temp = list[0];
		list[0] = list[1];
		list[1] = temp;
	}
}
