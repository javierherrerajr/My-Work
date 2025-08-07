import { render, screen } from '@testing-library/react';
import { CourseInfoPanel } from '../CourseInfoPanel';

// Mock the StarRating component
jest.mock('../StarRating', () => ({
  StarRating: ({ rating, size }: { rating: number; size: number }) => (
    <div data-testid="star-rating" data-rating={rating} data-size={size}>
      Mock Star Rating
    </div>
  ),
}));

describe('CourseInfoPanel', () => {
  const mockCourse = {
    id: 'CS100',
    name: 'Introduction to Computer Science',
    subject: 'Computer Science',
    department: 'Computer Science and Engineering',
    averageRating: 4.5,
    difficulty: 3,
    passRate: 85,
    prerequisites: [
      { id: 'CS010', name: 'Introduction to Programming' }
    ]
  };

  it('renders course ID and name', () => {
    render(<CourseInfoPanel course={mockCourse} />);
    
    expect(screen.getByText('CS100')).toBeInTheDocument();
    expect(screen.getByText('Introduction to Computer Science')).toBeInTheDocument();
  });

  it('renders average difficulty with one decimal place', () => {
    render(<CourseInfoPanel course={mockCourse} />);
    
    expect(screen.getByText('Avg. Difficulty: 4.5')).toBeInTheDocument();
  });

  it('renders StarRating component with correct props', () => {
    render(<CourseInfoPanel course={mockCourse} />);
    
    const starRating = screen.getByTestId('star-rating');
    expect(starRating).toHaveAttribute('data-rating', '4.5');
    expect(starRating).toHaveAttribute('data-size', '18');
  });

  it('applies correct styling classes', () => {
    render(<CourseInfoPanel course={mockCourse} />);
    
    const container = screen.getByText('CS100').closest('div');
    expect(container).toHaveClass('items-center');
    
    const courseId = screen.getByText('CS100');
    expect(courseId).toHaveClass('text-center', 'text-4xl', 'font-black', 'font-fredoka');
    
    const courseName = screen.getByText('Introduction to Computer Science');
    expect(courseName).toHaveClass('text-center', 'text-4xl', 'font-black', 'font-fredoka');
    
    const difficultyContainer = screen.getByText('Avg. Difficulty: 4.5').closest('div');
    expect(difficultyContainer).toHaveClass(
      'flex',
      'gap-4',
      'flex-wrap',
      'mt-2',
      'text-sm',
      'text-gray-800',
      'justify-center',
      'items-center'
    );
  });

  it('handles course with zero rating', () => {
    const courseWithZeroRating = {
      ...mockCourse,
      averageRating: 0
    };
    
    render(<CourseInfoPanel course={courseWithZeroRating} />);
    expect(screen.getByText('Avg. Difficulty: 0.0')).toBeInTheDocument();
  });

  it('handles course with decimal rating', () => {
    const courseWithDecimalRating = {
      ...mockCourse,
      averageRating: 4.333
    };
    
    render(<CourseInfoPanel course={courseWithDecimalRating} />);
    expect(screen.getByText('Avg. Difficulty: 4.3')).toBeInTheDocument();
  });
}); 