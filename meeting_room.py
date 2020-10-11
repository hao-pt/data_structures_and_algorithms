'''Meeting room
Given an array of time intervals (start, end) for meeting (possibly overlapping), 
find the minimum number of rooms required.

For example, given [(30, 75), (0, 50), (60, 150)], you should return 2.
[(0, 30), (5, 10), (15, 20)], return 2
[[1, 18], [18, 23], [15, 29], [4, 15], [2, 11], [5, 13]], return 4
'''
import heapq
class MeetingRoom:
    def meetingRoom(self, time_intervals):
        '''
        # Approach 1: sort meetings by starting time and do schedule by brutte-force
        # M is number of meetings, N is minimum number of required rooms 
        # Time complexity: Sorting: O(M*log(M)), meeting scheduling O(M*N) -> O(m*log(m))
        # Space: O(N)
        rooms = {} 
        # sort meeting based on start
        time_intervals.sort(key=lambda meeting: meeting[0])
        n = 0
        
        # meeting scheduling
        for meeting in time_intervals:
            # search for a suitable room where earliest meeting has end time less than start time of new meeting
            flag = False # determine whether any room fits with this meeting
            for i in range(n):
                if rooms[i][1] <= meeting[0]:
                    # update new meeting
                    rooms[i] = meeting
                    flag = True
                    break

            # if no room fit this meeting time, allocate new room for it
            if not flag:
                rooms[n] = meeting
                n += 1
                
        return n
        '''
        
        # Approach 2: use extra priority queue to store earliest endTime so far
        # M is number of meetings, N is minimum number of required rooms 
        # Time complexity: Sorting: O(M*log(M)), meeting scheduling O(M*log(N)) -> O(m*log(m))
        # Space: O(N)
        # sort meeting based on startTime
        time_intervals.sort(key=lambda meeting: meeting[0])
        pq = [time_intervals[0][1]] # add endTime of first meeting
        n = 1
        # meeting scheduling
        for i in range(1, len(time_intervals)):
            # if meeting i has startTime greater than endTime of earliest meeting so far
            # allocate new room
            if time_intervals[i][0] > pq[0]:
                n += 1
            else:
                # reuse open room and update earliest endTime
                heapq.heappop(pq)
            
            # add new endTime of current meeting and update earliest endTime
            heapq.heappush(pq, time_intervals[i][1])
        
        return n



if __name__ == "__main__":
    time_intervals = [[1, 18], [18, 23], [15, 29], [4, 15], [2, 11], [5, 13]]
    problem = MeetingRoom()
    ans = problem.meetingRoom(time_intervals)
    print(ans)
