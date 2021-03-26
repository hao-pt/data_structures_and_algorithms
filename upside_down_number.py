def upside_down_number(num):
    """
    Verify num is upside_down_number (or strobogrammatic number) whose numeral is rotationally symmetric, 
    so that it appears the same when rotated 180 degrees.
    Fox ex: 0, 1, 8, 11, 69, 88, 96, 101, 111, 181, 609, ...
    
    Idea: using two pointers to find a non-symmetric rotation between the leftmost and rightmost digit. 
    Time: O(n)
    Space: O(1) because there is fixed number of symmetric digits. 
    """
    rot = {"6": "9", "9": "6", "0": "0", "1":"1", "8":"8"}
    i = 0
    j = len(num)-1
    
    while i <= j:
        # check if left_most and right_most is different after rotating and the left_most can not be a symmetry of right_most
        if rot.get(num[i], -1) != rot.get(num[j], -2) and rot.get(num[i]) != num[j]:
            return False
        i += 1
        j -= 1
            
    return True
        
  
ans = upside_down_number("003821")
print(ans)
